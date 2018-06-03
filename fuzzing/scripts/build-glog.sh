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

dir=$PWD
pathToGlog="../../external/glog"

git submodule init "${pathToGlog}"
git submodule update "${pathToGlog}"

cd "${pathToGlog}"

git clean -dfqx
git reset --hard
git rev-parse HEAD

# The Google logging module cannot handle:
#   - Sanitizers (https://github.com/google/glog/issues/54)
#   - Coverage analysis

function strip {
    antiflags=(
        "-fcoverage-mapping"
        "-fprofile-instr-generate"
        "-fsanitize"
    )
    arr=( $1 )
    for f in "${arr[@]}"; do
        if [[ "${f}" == "" ]]; then
            continue
        fi
        for a in "${antiflags[@]}"; do
            if [[ "${f}" == *"${a}"* ]]; then
                continue 2
            fi
        done
        printf "%s " "${f}"
    done
}

export CFLAGS=$(strip "${CFLAGS}")
export CXXFLAGS=$(strip "${CXXFLAGS}")
export LDFLAGS=$(strip "${LDFLAGS}")

sh autogen.sh
sh configure

make -j$(nproc)

cd "${dir}"
