// facevisitor-properties.cpp
//
//   Implementation of FaceVisitorProperties.
//
// Copyright 2025 by
// The FreeType Project.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-properties.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftlcdfil.h>
#include <freetype/ftparams.h>

#include "utils/logging.h"


  freetype::FaceVisitorProperties::
  FaceVisitorProperties()
  {
  }


  void
  freetype::FaceVisitorProperties::
  run( Unique_FT_Face  face )
  {
    FT_Error      error;
    FT_Parameter  params[5];
    FT_Byte       payload[32] = { 
      0x01, 0x02, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00,
      0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80,
      0x10, 0x40, 0x70, 0x40, 0x10, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // 1. Unknown Tag
    params[0].tag  = FT_MAKE_TAG( 'f', 'u', 'z', 'z' );
    params[0].data = payload;

    // 2. Stem Darkening (Bool)
    // FT_PARAM_TAG_STEM_DARKENING might be in ftparams.h or similar
    // We try to use the macro if available, otherwise skip
#ifdef FT_PARAM_TAG_STEM_DARKENING
    FT_Bool darken = 1;
    params[1].tag  = FT_PARAM_TAG_STEM_DARKENING;
    params[1].data = &darken;
#else
    params[1].tag  = FT_MAKE_TAG( 's', 't', 'e', 'm' );
    params[1].data = payload;
#endif

    // 3. LCD Filter Weights
    params[2].tag  = FT_PARAM_TAG_LCD_FILTER_WEIGHTS;
    params[2].data = &payload[16]; // 5 bytes

    // 4. Random Seed
#ifdef FT_PARAM_TAG_RANDOM_SEED
    FT_Int32 seed = 12345;
    params[3].tag  = FT_PARAM_TAG_RANDOM_SEED;
    params[3].data = &seed;
#else
    params[3].tag  = 0xDEADBEEF;
    params[3].data = payload;
#endif

    // 5. Null Data
    params[4].tag  = FT_MAKE_TAG( 'n', 'u', 'l', 'l' );
    params[4].data = nullptr;

    error = FT_Face_Properties( face.get(), 5, params );
    LOG_FT_ERROR( "FT_Face_Properties", error );
  }
