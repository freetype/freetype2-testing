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
