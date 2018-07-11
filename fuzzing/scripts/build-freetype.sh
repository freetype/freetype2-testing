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
sh configure

make -j$(nproc)

cd "${dir}"
