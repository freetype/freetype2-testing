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
cd "${0%/*}" # go to /fuzzing/scripts

# We expect a bunch of flags coming in from the OSS-Fuzz framework;  in fact
# everything that is connected to compilers, sanitizers, coverage, ...  The
# only thing we want to touch here is setting the correct fuzzer flags since
# we build a few libraries that do not react well to the fuzzers' main
# function.

# Google's logging module has many issues with automated instrumentation.
# See `scripts/build-glog.sh' for details.  Thankfully, we're not interested
# in glog's internals and can simply skip the fuzzer instrumentation here.

bash build-glog.sh

cflags="${CFLAGS}"
cxxflags="${CXXFLAGS}"
ldflags="${LDFLAGS}"

export CFLAGS="${cflags} -fsanitize=fuzzer-no-link"
export CXXFLAGS="${cxxflags} -fsanitize=fuzzer-no-link"
export LDFLAGS="${ldflags} -fsanitize=fuzzer-no-link"

bash build-freetype.sh

# CMake has to add `-fsanitizer=fuzzer' itself:  `-fsanitizer=fuzzer' adds
# a `main' function which would cause CMake's setup process to fail.  See
# `fuzzing/CMakeLists.txt' for details.

export CFLAGS="${cflags}"
export CXXFLAGS="${cflags}"
export LDFLAGS="${ldflags}"

# Used by CMake to decide what to build:
export CMAKE_FUZZ_TARGET_TYPE="libfuzzer"

bash build-targets.sh

cd "${dir}"
