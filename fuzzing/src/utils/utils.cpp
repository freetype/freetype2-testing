// utils.cpp
//
//   Implementation of utils.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "utils/utils.h"

#include "utils/logging.h"


  using namespace fuzzing;


  Unique_FT_Face
  fuzzing::
  make_unique_face( FT_Face  face )
  {
    return Unique_FT_Face( face, FT_Done_Face );
  }


  Unique_FT_Glyph
  fuzzing::
  make_unique_glyph( FT_Glyph  glyph )
  {
    return Unique_FT_Glyph( glyph, FT_Done_Glyph );
  }


  Unique_FT_Glyph
  fuzzing::
  copy_unique_glyph( const Unique_FT_Glyph&  glyph )
  {
    FT_Error  error;

    FT_Glyph  raw_glyph;


    error = FT_Glyph_Copy( glyph.get(), &raw_glyph );

    if ( error != 0 )
    {
      LOG( ERROR ) << "FT_Glyph_Copy failed: " << error;
      return make_unique_glyph();
    }

    return make_unique_glyph( raw_glyph );
  }
