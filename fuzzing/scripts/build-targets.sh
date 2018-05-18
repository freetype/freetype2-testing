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
cd ..

rm -rf build
mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)

cd "${dir}"
