#!/bin/bash
set -euxo pipefail

# Copyright 2018 by
# Armin Hasitzka.
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.

dir="${PWD}"
pathToFreeType=$(readlink -f "../../external/freetype2")

git submodule init "${pathToFreeType}"

# We always want to run the latest version of FreeType:
git submodule update --remote "${pathToFreeType}"

cd "${pathToFreeType}"

git clean -dfqx
git reset --hard
git rev-parse HEAD

sh autogen.sh

# Having additional libraries is pain since they have to be linked statically
# for OSS-Fuzz.  Should additional libraries be required, they have to be
# linked properly in `fuzzing/src/fuzzers/CMakeLists.txt'.

sh configure \
   --enable-static=yes \
   --enable-shared=no \
   --with-bzip2=no \
   --with-harfbuzz=no \
   --with-png=no  \
   --with-zlib=no

make -j$(nproc)

cd "${dir}"
