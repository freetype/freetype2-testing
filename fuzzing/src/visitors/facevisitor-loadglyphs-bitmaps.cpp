// facevisitor-loadglyphs-bitmaps.cpp
//
//   Implementation of FaceVisitorLoadGlyphsBitmaps.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-loadglyphs-bitmaps.h"


  FaceVisitorLoadGlyphsBitmaps::
  FaceVisitorLoadGlyphsBitmaps( FT_Long  num_used_glyphs )
    : FaceVisitorLoadGlyphs( num_used_glyphs )
  {
    (void) add_mode( FT_LOAD_DEFAULT             );
    (void) add_mode( FT_LOAD_VERTICAL_LAYOUT     );
    (void) add_mode( FT_LOAD_LINEAR_DESIGN       );
    (void) add_mode( FT_LOAD_COLOR               );
    (void) add_mode( FT_LOAD_BITMAP_METRICS_ONLY );
  }
