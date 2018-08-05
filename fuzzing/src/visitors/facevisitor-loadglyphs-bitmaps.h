// facevisitor-loadglyphs-bitmaps.h
//
//   Load bitmap glyphs with a variety of different load flags.
//
//   Drivers: all
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef VISITORS_FACE_VISITOR_LOAD_GLYPHS_BITMAPS_H_
#define VISITORS_FACE_VISITOR_LOAD_GLYPHS_BITMAPS_H_


#include "visitors/facevisitor-loadglyphs.h"


  class FaceVisitorLoadGlyphsBitmaps
  : public FaceVisitorLoadGlyphs
  {
  public:


    FaceVisitorLoadGlyphsBitmaps( FT_Long  num_used_glyphs );


    FaceVisitorLoadGlyphsBitmaps(
      const FaceVisitorLoadGlyphsBitmaps& ) = delete;
    FaceVisitorLoadGlyphsBitmaps& operator= (
      const FaceVisitorLoadGlyphsBitmaps& ) = delete;


    virtual
    ~FaceVisitorLoadGlyphsBitmaps( void ) {}
  };


#endif // VISITORS_FACE_VISITOR_LOAD_GLYPHS_BITMAPS_H_
