#!/bin/bash
set -eo pipefail

# Copyright 2018 by
# Armin Hasitzka.
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.

dir="${PWD}"
cd "${0%/*}" # go to `fuzzing/scripts'

if [[ "$#" == "1" && "${1}" == "--help" ]]; then
    cat <<EOF

usage: ${0} [OPTIONS]

This script listens to a few environmental variables.  It is not mandatory to
set any of these variables but if they are set, they will be used.

  CFLAGS    Additional C compiler flags.
  CXXFLAGS  Additional C++ compiler flags.
  LDFLAGS   Additional linker flags.

OPTIONS:

  --help  Print usage information.

EOF

    exit
fi

# ----------------------------------------------------------------------------
# settings:

ansi_reset="\e[0m"
ansi_bold="\e[1m"
ansi_underline="\e[4m"
ansi_yellow="\e[33m"

build_type=
build_asan=
build_ubsan=
build_coverage=
build_debugging=
build_ft_trace=

printf "local: [%s], global: [%s]\n" "${build_type}" "${BUILD_TYPE}"

# ----------------------------------------------------------------------------
# helpers:

# print question:
function print_q {
    printf "\n${ansi_bold}%s${ansi_reset}\n" "${1}"
}

# print info:
function print_info {
    if [[ "$#" == "1" ]]; then
        printf "  %s\n" "${1}"
    elif [[ "$#" == "2" ]]; then
        printf "  ${ansi_yellow}%s${ansi_reset}: %s\n" "${1}" "${2}"
    else
        exit 66
    fi
}

# print url:
function print_url {
    printf "  ${ansi_underline}%s${ansi_reset}\n" "${1}"
}

# print selection
# param 1: value
# param 2: cmp value
# param 3: string
function print_sel {
    if [[ "${1}" == "${2}" ]]; then
        printf "\n  selection: ${ansi_yellow}%s${ansi_reset}\n" "${3}"
    fi
}

# param 1: a list of options like "a|b|c"
# param 2 (optional): a default option like "a"
function ask_user {
    options="${1}"
    if [[ "$#" == "2" ]]; then
        options="${options}, default: ${2}"
    fi
    while : ; do
        read -p "(${options}) > " answer
        answer=$(echo "${answer}" | tr '[:upper:]' '[:lower:]')
        if [[ "${answer}" == "" && "$#" == "2" ]]; then
            echo "${2}"
            break
        fi
        if [[ "${1}" == *"|${answer}|"* ||
                  "${1}" == *"|${answer}" ||
                  "${1}" == "${answer}|"* ]]; then
            echo "${answer}"
            break
        fi
    done
}

# ----------------------------------------------------------------------------
# interaction:

printf "${ansi_yellow}"
printf " ____ ____  ____ ____ ______    __ ___  ____\n"
printf "|  __)  _ \|  __)  __)_   __)  / /  _ \|  __)\n"
printf "| |__| |_) ) |__| |__  | | \ \/ /| |_) ) |__\n"
printf "|  __)    /|  __)  __) | |  \  / |  __/|  __)\n"
printf "| |  | |\ \| |__| |__  | |  / /  | |   | |__\n"
printf "|_|  |_| \_\____)____) |_| /_/   |_|   |____)\n\n"
printf "${ansi_reset}"
printf "               Custom Build\n"

print_q "Build the driver or the fuzzer?"
print_info "driver" "run selected samples or failed instances"
print_info "fuzzer" "fuzz a corpus of samples with libFuzzer"
printf "\n"
build_type=$(ask_user "d|f")
print_sel "${build_type}" "d" "driver"
print_sel "${build_type}" "f" "fuzzer"

print_q "Add the AddressSanitizer?"
print_url "https://clang.llvm.org/docs/AddressSanitizer.html"
printf "\n"
build_asan=$(ask_user "y|n" "y")
print_sel "${build_asan}" "y" "yes"
print_sel "${build_asan}" "n" "no"

print_q "Add the UndefinedBehaviorSanitizer?"
print_url "https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html"
printf "\n"
build_ubsan=$(ask_user "y|n" "y")
print_sel "${build_ubsan}" "y" "yes"
print_sel "${build_ubsan}" "n" "no"

print_q "Add coverage instrumentation?"
print_url "https://clang.llvm.org/docs/SourceBasedCodeCoverage.html"
printf "\n"
build_coverage=$(ask_user "y|n" "n")
print_sel "${build_coverage}" "y" "yes"
print_sel "${build_coverage}" "n" "no"

if [[ "${build_asan}" == "y" || "${build_ubsan}" == "y" ]]; then
    build_debugging="1"
else
    print_q "Add debugging flags?"
    print_info "0" "compile with '-g -O0'"
    print_info "1" "compile with '-g -O1'"
    print_info "2" "compile with '-g -O2'"
    print_info "3" "compile with '-g -O3'"
    print_info "n" "compile without debugging flags"
    printf "\n"
    build_debugging=$(ask_user "0|1|2|3|n" "1")
    print_sel "${build_debugging}" "0" "-g O0"
    print_sel "${build_debugging}" "1" "-g O1"
    print_sel "${build_debugging}" "2" "-g O2"
    print_sel "${build_debugging}" "3" "-g O3"
    print_sel "${build_debugging}" "n" "no"
fi

if [[ "${build_type}" == "f" ]]; then
    build_glog="n"
else
    print_q "Use Glog logger?"
    print_url "https://github.com/google/glog"
    print_info "no" "logging will be compiled out and glog will not be linked"
    printf "\n"
    build_glog=$(ask_user "y|n" "n")
    print_sel "${build_glog}" "y" "yes"
    print_sel "${build_glog}" "n" "no"
fi

if [[ "${build_type}" == "f" ]]; then
    build_ft_trace="n"
else
    print_q "Add FreeType tracing?"
    print_info "yes" "activate 'FT_DEBUG_LEVEL_{TRACE,ERROR}'"
    printf "\n"
    build_ft_trace=$(ask_user "y|n" "n")
    print_sel "${build_ft_trace}" "y" "yes"
    print_sel "${build_ft_trace}" "n" "no"
fi

# ----------------------------------------------------------------------------
# assemble the flags:

cflags="${CFLAGS}"
cxxflags="${CXXFLAGS}"
ldflags="${LDFLAGS}"

if [[ "${build_debugging}" != "n" ]]; then
    cflags="${cflags} -g -O${build_debugging}"
    cxxflags="${cxxflags} -g -O${build_debugging}"
fi

if [[ "${build_asan}" == "y" ]]; then
    cflags="${cflags} -fsanitize=address -fsanitize-address-use-after-scope"
    cxxflags="${cxxflags} -fsanitize=address -fsanitize-address-use-after-scope"
    ldflags="${ldflags} -fsanitize=address"
fi

if [[ "${build_ubsan}" == "y" ]]; then
    cflags="${cflags} -fsanitize=undefined"
    cxxflags="${cxxflags} -fsanitize=undefined"
    ldflags="${ldflags} -fsanitize=undefined"
fi

if [[ "${build_coverage}" == "y" ]]; then
    cflags="${cflags} -fprofile-instr-generate -fcoverage-mapping"
    cxxflags="${cxxflags} -fprofile-instr-generate -fcoverage-mapping"
    ldflags="${ldflags} -fprofile-instr-generate"
fi

if [[ "${build_ft_trace}" == "y" ]]; then
    cflags="${cflags} -DFT_DEBUG_LEVEL_TRACE -DFT_DEBUG_LEVEL_ERROR"
    cxxflags="${cxxflags} -DFT_DEBUG_LEVEL_TRACE -DFT_DEBUG_LEVEL_ERROR"
fi

export CC="clang"
export CXX="clang++"

if [[ "${build_type}" == "d" ]]; then
    export CFLAGS="${cflags}"
    export CXXFLAGS="${cxxflags}"
elif [[ "${build_type}" == "f" ]]; then
    export CFLAGS="${cflags} -fsanitize=fuzzer-no-link"
    export CXXFLAGS="${cxxflags} -fsanitize=fuzzer-no-link"
else
    exit 66
fi

export LDFLAGS="${ldflags}"

# ----------------------------------------------------------------------------
# build libarchive + FreeType:

bash build-libarchive.sh
bash build-freetype.sh

# ----------------------------------------------------------------------------
# build the targets:

if [[ "${build_type}" == "f" ]]; then
    export CMAKE_FUZZING_ENGINE="-fsanitize=fuzzer"
elif [[ "${build_type}" != "d" ]]; then
    exit 66
fi

if [[ "${build_glog}" == "y" ]]; then
    export CMAKE_USE_LOGGER_GLOG=1
fi

bash build-targets.sh

cd "${dir}"
