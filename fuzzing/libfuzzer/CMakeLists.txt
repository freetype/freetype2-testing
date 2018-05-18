# CMakeLists.txt
#
# Copyright 2018 by
# Armin Hasitzka.
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.

add_executable(libfuzzer-legacy ../../freetype2/src/tools/ftfuzzer/ftfuzzer.cc)
target_link_libraries(libfuzzer-legacy PRIVATE archive freetype)
