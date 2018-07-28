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

path_to_build=$( readlink -f "../build" )

if [[ "${#}" == "0" || "${1}" != "--no-init" ]]; then

    mkdir -p "${path_to_build}" && cd "${path_to_build}"

    # Remove all files and folders in `fuzzing/build' except for the folder
    # `bin':

    find .              \
         -maxdepth 1    \
         -type f        \
         -exec rm {} \;

    find .                 \
         -maxdepth 1       \
         -type d           \
         ! -name bin       \
         -exec rm -r {} \;

    cmake -DCMAKE_BUILD_TYPE=Debug ..
fi

if [[ -d "${path_to_build}" ]]; then
   cd "${path_to_build}"
   make -j$( nproc )
fi

cd "${dir}"
