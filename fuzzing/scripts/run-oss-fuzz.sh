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
cd "${0%/*}" # go to this script's directory

# the fuzzer should always run on the latest versions of everything
git submodule update --recursive --remote

export CC="clang"
export CXX="clang++"

sanitize_flags="-fsanitize=address,undefined -fsanitize-address-use-after-scope"

cflags_vanilla="${CFLAGS} -g -O1 ${sanitize_flags}"
cxxflags_vanilla="${CXXFLAGS} -g -O1 -std=c++11 ${sanitize_flags}"
ldflags_vanilla="${LDFLAGS} ${sanitize_flags}"

export CFLAGS="${cflags_vanilla} -fsanitize=fuzzer-no-link"
export CXXFLAGS="${cxxflags_vanilla} -fsanitize=fuzzer-no-link"
export LDFLAGS="${ldflags_vanilla} -fsanitize=fuzzer-no-link"

bash build-freetype.sh

# CMake has to add -fsanitizer=fuzzer as the setup process would fail
# when calling CMake with that flag.  See fuzzing/CMakeLists.txt for
# details.
export CFLAGS="${cflags_vanilla}"
export CXXFLAGS="${cflags_vanilla}"
export LDFLAGS="${ldflags_vanilla}"

# used by CMake to decide what to build
export CMAKE_FUZZ_TARGET_TYPE="libfuzzer"

bash build-targets.sh

cd "${dir}"
