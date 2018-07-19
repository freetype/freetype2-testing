// outlines.h
//
//   Fuzz target for glyph outlines.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_GLYPHS_OUTLINES_H_
#define TARGETS_GLYPHS_OUTLINES_H_


#include "targets/base.h"


  class GlyphsOutlinesFuzzTarget
  : public FuzzTarget
  {
  public:


    GlyphsOutlinesFuzzTarget( void );
  };


#endif // TARGETS_GLYPHS_OUTLINES_H_
