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
built_ft_trace=

# ----------------------------------------------------------------------------
# helpers:

# print question:
function print_q {
    printf "\n${ansi_bold}%s${ansi_reset}\n" "${1}"
}

# print info:
function print_i {
    if [[ $# == 1 ]]; then
        printf "  %s\n" "${1}"
    elif [[ $# == 2 ]]; then
        printf "  ${ansi_yellow}%s${ansi_reset}: %s\n" "${1}" "${2}"
    else
        exit 66
    fi
}

# print url:
function print_url {
    printf "  ${ansi_underline}%s${ansi_reset}\n" "${1}"
}

function ask_user {
    while : ; do
        read -p "(${1} or ${2}) > " answer
        if [[ "${answer}" == "${1}" || "${answer}" == "${2}" ]]; then
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
print_i "driver" "run selected samples or failed instances"
print_i "fuzzer" "fuzz a corpus of samples with libFuzzer"
printf "\n"

build_type=$(ask_user "d" "f")

print_q "Add the AddressSanitizer?"
print_url "https://clang.llvm.org/docs/AddressSanitizer.html"
printf "\n"

build_asan=$(ask_user "y" "n")

print_q "Add the UndefinedBehaviorSanitizer?"
print_url "https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html"
printf "\n"

build_ubsan=$(ask_user "y" "n")

print_q "Add coverage instrumentation?"
print_url "https://clang.llvm.org/docs/SourceBasedCodeCoverage.html"
printf "\n"

build_coverage=$(ask_user "y" "n")

if [[ "${build_asan}" == "y" || "${build_ubsan}" == "y" ]]; then
    build_debugging="y"
else
    print_q "Add debugging flags?"
    print_i "yes" "compile with '-g -O1'"
    printf "\n"

    build_debugging=$(ask_user "y" "n")
fi

print_q "Use Glog logger?"
print_url "https://github.com/google/glog"
print_i "no" "logging will be compiled out and glog will not be linked"
printf "\n"

build_glog=$(ask_user "y" "n")

print_q "Add FreeType tracing?"
print_i "yes" "activate 'FT_DEBUG_LEVEL_{TRACE,ERROR}'"
printf "\n"

build_ft_trace=$(ask_user "y" "n")

# ----------------------------------------------------------------------------
# assemble the flags:

cflags="${CFLAGS}"
cxxflags="${CXXFLAGS}"
ldflags="${LDFLAGS}"

if [[ "${build_debugging}" == "y" ]]; then
    cflags="${cflags} -g -O1"
    cxxflags="${cxxflags} -g -O1"
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

if [[ "${build_trace}" == "y" ]]; then
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
# build FreeType:

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
