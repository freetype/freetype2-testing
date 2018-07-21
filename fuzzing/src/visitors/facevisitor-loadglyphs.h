// facevisitor-loadglyphs.h
//
//   Load a bunch of glyphs with a variety of different load flags.
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


#ifndef VISITORS_FACE_VISITOR_LOAD_GLYPHS_H_
#define VISITORS_FACE_VISITOR_LOAD_GLYPHS_H_


#include <vector>

#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace std;


  class FaceVisitorLoadGlyphs
  : public FaceVisitor
  {
  public:


    FaceVisitorLoadGlyphs( void ) {}


    FaceVisitorLoadGlyphs( const FaceVisitorLoadGlyphs& ) = delete;
    FaceVisitorLoadGlyphs& operator= (
      const FaceVisitorLoadGlyphs& ) = delete;


    virtual
    ~FaceVisitorLoadGlyphs( void ) {}


    void
    run( Unique_FT_Face  face )
    override;


  protected:


    // Description:
    //   Set load flags that will all be used in `run()'.
    //
    // Input:
    //   flags ::
    //     A set of flags.

    void
    add_load_flags( FT_Int32  flags );


  private:


    static const FT_Long  GLYPH_INDEX_MAX = 30;

    vector<FT_Int32>  load_flags;
  };


#endif // VISITORS_FACE_VISITOR_LOAD_GLYPHS_H_
