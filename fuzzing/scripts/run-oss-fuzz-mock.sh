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

# ----------------------------------------------------------------------------
# system settings:

SRC=$(readlink -f "../..")            # root of the repository
OUT=$(readlink -f "../oss-fuzz-mock") # root of the fuzzer

# This script should only be used to verify that fuzzing works in general.
# All the heavy lifting will be done by OSS-Fuzz which is why 100 runs are
# more than enough.

fuzzer_runs=100

do_build=1   # build the fuzzers
do_prepare=1 # prepare all corpora
do_fuzz=1    # run the fuzzers on the prepared corpora
do_analyse=1 # prepare and print analysis of the fuzzing phase

# ----------------------------------------------------------------------------
# flags that are set by OSS-Fuzz:

cflags=(
    "-O1"
    "-gline-tables-only"
    "-fno-omit-frame-pointer"
)

ldflags=(
)

sanitize_flags=(
    "-fsanitize=address,undefined"
    "-fsanitize-address-use-after-scope"
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

export CFLAGS="${CFLAGS} ${cflags} ${sanitize_flags} ${coverage_cflags}"
export CXXFLAGS="${CXXFLAGS} ${cflags} ${sanitize_flags} ${coverage_cflags}"

export LDFLAGS="${LDFLAGS} ${ldflags} ${sanitize_flags} ${coverage_ldflags}"

# ----------------------------------------------------------------------------
# helpful defines:

fuzzing_base_dir="${SRC}/fuzzing"
corpora_base_dir="${fuzzing_base_dir}/corpora"
bin_base_dir="${fuzzing_base_dir}/build/bin"
freetype_base_dir="${SRC}/external/freetype2"

fuzzers=(
    "cff"
    "cidtype1"
    "truetype"
    "type1"
)

# ----------------------------------------------------------------------------
# build the fuzzers:

if [[ "${do_build}" == "1" ]]; then
    bash "${fuzzing_base_dir}/scripts/build-oss-fuzz.sh"
fi

# ----------------------------------------------------------------------------
# prepare the corpora:

if [[ "${do_prepare}" == "1" ]]; then

    rm -rf "${OUT}"
    mkdir "${OUT}"

    for fuzzer in "${fuzzers[@]}"; do
        cp "${bin_base_dir}/${fuzzer}" "${OUT}/${fuzzer}"
        mkdir "${OUT}/${fuzzer}_seed_corpus"
        find "${corpora_base_dir}/${fuzzer}" \
             -type f \
             ! -name "README.md" \
             -exec cp {} "${OUT}/${fuzzer}_seed_corpus" \;
    done
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
             "${freetype_base_dir}"/objs/.libs/libfreetype.so
fi
