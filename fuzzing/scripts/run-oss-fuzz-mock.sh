#!/bin/bash
set -exo pipefail

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
# system settings:

export SRC=$(readlink -f "../..")             # checkout source files
export WORK=$(readlink -f "../oss-fuzz-mock") # storing intermediate files
export OUT=$(readlink -f "../oss-fuzz-mock")  # store build artifacts

# this mock: OUT == WORK
rm -rf "${OUT}"
mkdir "${OUT}"

# This script should only be used to verify that fuzzing works in general.
# All the heavy lifting will be done by OSS-Fuzz which is why 100 runs are
# more than enough.

fuzzer_runs=100

do_build=1   # build the fuzzers
do_prepare=1 # prepare all corpora
do_fuzz=1    # run the fuzzers on the prepared corpora
do_analyse=1 # prepare and print analysis of the fuzzing phase

# ----------------------------------------------------------------------------
# (important) flags that are set by OSS-Fuzz:

cflags=(
    "-O1"
    "-gline-tables-only"
    "-fno-omit-frame-pointer"
)

ldflags=(
)

sanitize_cflags=(
    "-fsanitize=fuzzer-no-link"
    "-fsanitize=address,undefined"
    "-fsanitize-address-use-after-scope"
)

sanitize_ldflags=(
    "-fsanitize=address,undefined"
)
    
coverage_cflags=(
    "-fprofile-instr-generate"
    "-fcoverage-mapping"
)

coverage_ldflags=(
    "-fprofile-instr-generate"
)

export CC="clang"
export CXX="clang++"

export CFLAGS="${CFLAGS} ${cflags[@]} ${sanitize_cflags[@]} ${coverage_cflags[@]}"
export CXXFLAGS="${CXXFLAGS} ${cflags[@]} ${sanitize_cflags[@]} ${coverage_cflags[@]}"

export LDFLAGS="${LDFLAGS} ${ldflags[@]} ${sanitize_ldflags[@]} ${coverage_ldflags[@]}"

# ----------------------------------------------------------------------------
# helpful defines:

fuzzers=(
    "legacy"
    "cff"
    "cidtype1"
    "truetype"
    "type1"
)

# ----------------------------------------------------------------------------
# build the fuzzers:

# Tell CMake what fuzzing engine to link:
export CMAKE_FUZZING_ENGINE="-fsanitize=fuzzer"

if [[ "${do_build}" == "1" ]]; then
    bash "${SRC}/fuzzing/scripts/build-fuzzers.sh"
fi

# ----------------------------------------------------------------------------
# prepare the fuzzers and corpora:

if [[ "${do_prepare}" == "1" ]]; then
    bash "${SRC}/fuzzing/scripts/prepare-oss-fuzz.sh"
fi

# ----------------------------------------------------------------------------
# run the fuzzers:

cd "${OUT}"

if [[ "${do_fuzz}" == "1" ]]; then
    for fuzzer in "${fuzzers[@]}"; do
        GLOG_minloglevel=99 "./${fuzzer}" \
		                    "-runs=${fuzzer_runs}" \
		                    -print_final_stats=1 \
		                    "${fuzzer}_seed_corpus"
    done
fi

# ----------------------------------------------------------------------------
# analyse:

if [[ "${do_fuzz}" == "1" && "${do_analyse}" == "1" ]]; then
    llvm-profdata merge -sparse *.profraw -o fuzzing.profdata
    llvm-cov report \
             -instr-profile=fuzzing.profdata \
             "${SRC}/external/freetype2/objs/.libs/libfreetype.so"
fi

cd "${dir}"
