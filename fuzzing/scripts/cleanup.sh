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
cd $( dirname $( readlink -f "${0}" ) ) # go to `/fuzzing/scripts'

base_path=$( readlink -f ../.. )

path_to_freetype="${base_path}/external/freetype2"
path_to_glog="${base_path}/external/glog"
path_to_libarchive="${base_path}/external/libarchive"

cd "${base_path}"
git reset --hard
git clean -dfqx
git checkout "external/*"

cd "${path_to_freetype}"
git reset --hard
git clean -dfqx

cd "${path_to_glog}"
git reset --hard
git clean -dfqx

cd "${path_to_libarchive}"
git reset --hard
git clean -dfqx

cd "${dir}"
