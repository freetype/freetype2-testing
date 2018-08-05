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
  FaceVisitorLoadGlyphsOutlines( FT_Long  num_used_glyphs )
    : FaceVisitorLoadGlyphs( num_used_glyphs )
  {
    // Note: the auto-hinter has its own visitor.

    FT_Int32  flags = FT_LOAD_NO_BITMAP | FT_LOAD_NO_AUTOHINT;


    // Rotate by 3 degrees.
    // Coefficients are in 16.16 fixed-point format.
    matrix.xx = 0x10000L *  0.99862;
    matrix.xy = 0x10000L * -0.05233;
    matrix.yx = 0x10000L *  0.05233;
    matrix.yy = 0x10000L *  0.99862;

    // Coordinates are expressed in 1/64th of a pixel.
    delta.x = -3 * 64;
    delta.y =  3 * 64;

    (void) add_transformation( nullptr, &delta  );
    (void) add_transformation( &matrix, nullptr );
    (void) add_transformation( &matrix, &delta  );

    (void) add_mode( flags,                        FT_RENDER_MODE_NORMAL );

    (void) add_mode( flags | FT_LOAD_NO_SCALE                            );
    (void) add_mode( flags | FT_LOAD_NO_HINTING,   FT_RENDER_MODE_NORMAL );
    (void) add_mode( flags | FT_LOAD_VERTICAL_LAYOUT                     );
    (void) add_mode( flags | FT_LOAD_PEDANTIC                            );
    (void) add_mode( flags | FT_LOAD_LINEAR_DESIGN                       );
    (void) add_mode( flags | FT_LOAD_COMPUTE_METRICS                     );
    
    (void) add_mode( flags | FT_LOAD_TARGET_LIGHT, FT_RENDER_MODE_LIGHT  );
    (void) add_mode( flags | FT_LOAD_TARGET_MONO,  FT_RENDER_MODE_MONO   );
    (void) add_mode( flags | FT_LOAD_TARGET_LCD,   FT_RENDER_MODE_LCD    );
    (void) add_mode( flags | FT_LOAD_TARGET_LCD_V, FT_RENDER_MODE_LCD_V  );
  }
