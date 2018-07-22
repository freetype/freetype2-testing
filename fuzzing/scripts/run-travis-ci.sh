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

sanitize_flags=(
    "-fsanitize=address,undefined"
    "-fsanitize-address-use-after-scope"
)

export CC="clang"
export CXX="clang++"

export CFLAGS="${CFLAGS} -g -O1 ${sanitize_flags[@]}"
export CXXFLAGS="${CXXFLAGS} -g -O1 -std=c++14 ${sanitize_flags[@]}"
export LDFLAGS="${LDFLAGS} ${sanitize_flags[@]}"

bash build-libarchive.sh

bash build-freetype.sh

bash build-targets.sh

cd ../build

CTEST_OUTPUT_ON_FAILURE=1 make test -j$(nproc)

cd "${dir}"
