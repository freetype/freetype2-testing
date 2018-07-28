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

path_to_src=$( readlink -f "../../external/glog" )
path_to_build="${path_to_src}/build"

if [[ "${#}" == "0" || "${1}" != "--no-init" ]]; then

    git submodule init             "${path_to_src}"
    git submodule update --depth 1 "${path_to_src}"

    cd "${path_to_src}"

    git clean -dfqx
    git reset --hard
    git rev-parse HEAD

    cmake -H.                 \
          -Bbuild             \
          -G "Unix Makefiles" \
          -DWITH_GFLAGS=OFF   \
          -DBUILD_TESTING=OFF
fi

if [[ -d "${path_to_build}" ]]; then
    cd "${path_to_build}"
    make -j$( nproc )
fi

cd "${dir}"
