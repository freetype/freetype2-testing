// facevisitor-loadglyphs-outlines.cpp
//
//   Implementation of FaceVisitorLoadGlyphsOutlines.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-loadglyphs-outlines.h"


  FaceVisitorLoadGlyphsOutlines::
  FaceVisitorLoadGlyphsOutlines()
  {
    FT_Int32  flags = FT_LOAD_NO_BITMAP | FT_LOAD_RENDER;

    (void) add_load_flags( flags );

    (void) add_load_flags( flags | FT_LOAD_NO_SCALE );
    (void) add_load_flags( flags | FT_LOAD_NO_HINTING );
    (void) add_load_flags( flags | FT_LOAD_VERTICAL_LAYOUT );
    (void) add_load_flags( flags | FT_LOAD_FORCE_AUTOHINT );
    (void) add_load_flags( flags | FT_LOAD_PEDANTIC );
    (void) add_load_flags( flags | FT_LOAD_NO_RECURSE );
    (void) add_load_flags( flags | FT_LOAD_LINEAR_DESIGN );
    (void) add_load_flags( flags | FT_LOAD_NO_AUTOHINT );
    (void) add_load_flags( flags | FT_LOAD_COMPUTE_METRICS );
    
    (void) add_load_flags( flags | FT_LOAD_MONOCHROME );
    (void) add_load_flags( flags | FT_LOAD_TARGET_LIGHT );
    (void) add_load_flags( flags | FT_LOAD_TARGET_MONO );
    (void) add_load_flags( flags | FT_LOAD_TARGET_LCD );
    (void) add_load_flags( flags | FT_LOAD_TARGET_LCD_V );
  }
