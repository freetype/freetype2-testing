// facevisitor-renderglyphs.h
//
//   Render a bunch of glyphs with a variety of different modes.
//
//   Drivers:
//     - CID Type 1
//     - CFF
//     - PFR
//     - TrueType
//     - Type 1
//     - Type 42
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef VISITORS_FACE_VISITOR_RENDER_GLYPHS_H_
#define VISITORS_FACE_VISITOR_RENDER_GLYPHS_H_


#include <vector>

#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace std;


  class FaceVisitorRenderGlyphs
  : public FaceVisitor
  {
  public:


    FaceVisitorRenderGlyphs( void ) {}


    FaceVisitorRenderGlyphs( const FaceVisitorRenderGlyphs& ) = delete;
    FaceVisitorRenderGlyphs& operator= (
      const FaceVisitorRenderGlyphs& ) = delete;


    virtual
    ~FaceVisitorRenderGlyphs( void ) {}


    void
    run( Unique_FT_Face  face )
    override;


  private:


    static const FT_Long  GLYPH_INDEX_MAX = 5;

    static const vector<pair<FT_Int32, FT_Render_Mode>>  RENDER_MODES;
  };


#endif // VISITORS_FACE_VISITOR_RENDER_GLYPHS_H_
