#!/bin/bash
set -exo pipefail

# Copyright 2019 by
# Armin Hasitzka.
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.

dir="${PWD}"
cd $( dirname $( readlink -f "${0}" ) ) # go to `/fuzzing/scripts/build'

path_to_boost=$( readlink -f "../../../external/boost" )

if [[ "${#}" == "0" || "${1}" != "--no-init" ]]; then

    git submodule update --init "${path_to_boost}"

    cd "${path_to_boost}"

    git clean -dfqx
    git reset --hard
    git rev-parse HEAD

    mods=(
        "libs/config"
        "libs/core"
        "tools"
    )
    
    for m in "${mods[@]}"; do
        git submodule update --init "${m}"
    done

    sh ./bootstrap.sh

    ./b2                     \
        variant=release      \
        link=static          \
        runtime-link=static  \

fi

cd "${dir}"
