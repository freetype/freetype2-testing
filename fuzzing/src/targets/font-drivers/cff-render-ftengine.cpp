// cff-render-ftengine.cpp
//
//   Implementation of CffRenderFtEngineFuzzTarget.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/font-drivers/cff-render-ftengine.h"


  CffRenderFtEngineFuzzTarget::
  CffRenderFtEngineFuzzTarget( void )
  {
    (void) set_property( "cff", "hinting-engine", &HINTING_FREETYPE );
  }
