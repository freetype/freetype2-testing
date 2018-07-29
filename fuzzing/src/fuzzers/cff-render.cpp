// cff-render.cpp
//
//   Fuzz target to render CFF fonts.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/font-drivers/cff-render.h"


  static CffRenderFuzzTarget  target;


  extern "C" int
  LLVMFuzzerTestOneInput( const uint8_t*  data,
                          size_t          size )
  {
    (void) target.run( data, size );
    return 0;
  }
