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

path_to_freetype=$( readlink -f "../../external/freetype2" )

if [[ "${#}" == "0" || "${1}" != "--no-init" ]]; then

    git submodule init "${path_to_freetype}"

    # We always want to run the latest version of FreeType:
    git submodule update --depth 1 --remote "${path_to_freetype}"

    cd "${path_to_freetype}"

    git clean -dfqx
    git reset --hard
    git rev-parse HEAD

    # Manipulating `ftoption.h' to enable non-standard features of FreeType.
    # There are prettier ways to achieve that, however, this is the simplest:

    git apply "../../fuzzing/settings/freetype2/ftoption.patch"

    sh autogen.sh

    # Having additional libraries is pain since they have to be linked
    # statically for OSS-Fuzz.  Should additional libraries be required, they
    # have to be linked properly in `fuzzing/src/fuzzers/CMakeLists.txt'.

    sh configure          \
       --enable-static    \
       --disable-shared   \
       --without-bzip2    \
       --without-harfbuzz \
       --without-png      \
       --without-zlib
fi

cd "${path_to_freetype}"

if [[ -f "Makefile" ]]; then
    make -j$( nproc )
fi

cd "${dir}"
