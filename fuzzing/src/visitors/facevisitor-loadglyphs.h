// facevisitor-loadglyphs.h
//
//   Load and render a bunch of glyphs with a variety of different flags and
//   modes.
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


    // @See: `FaceVisitorLoadGlyphs::set_num_used_glyphs()'.

    FaceVisitorLoadGlyphs( FT_Long  num_used_glyphs );


    FaceVisitorLoadGlyphs( const FaceVisitorLoadGlyphs& ) = delete;
    FaceVisitorLoadGlyphs& operator= (
      const FaceVisitorLoadGlyphs& ) = delete;


    virtual
    ~FaceVisitorLoadGlyphs( void ) {}


    void
    run( Unique_FT_Face  face )
    override;


    // @Description:
    //   Set the amount of glyphs that will be loaded/rendered per setting.
    //   Note that this function HAS to be called BEFORE
    //   `FaceVisitorLoadGlyphs::run()' or this visitor will fail.  This
    //   function also gets called implicitely in a dedicated constructor.
    //
    // @Input:
    //   max ::
    //     Has to ba a value in the range of [1, LONG_MAX) or calling
    //     `FaceVisitorLoadGlyphs::run()' will fail.

    void
    set_num_used_glyphs( FT_Long  glyphs );


  protected:


    // @Description:
    //   Add a transformation that will be used with all load flags.
    //   Note:  the "empty" transformation (no transformation at all) will
    //   always be added automatically.
    //
    // @Input:
    //   matrix ::
    //     See `FT_Set_Transform'.
    //
    //   vector ::
    //     See `FT_Set_Transform'.

    void
    add_transformation( FT_Matrix*  matrix,
                        FT_Vector*  delta );


    // @See: `FaceVisitorLoadGlyphs::add_mode()'.

    void
    add_mode( FT_Int32  load_flags );


    // @Description:
    //   Set a combination of load flags and render modes that will be used in
    //   `run()'.
    //
    // @Input:
    //   load_flags ::
    //     A set of load flags.
    //
    //   render_mode ::
    //     A render mode.

    void
    add_mode( FT_Int32        load_flags,
              FT_Render_Mode  render_mode );


  private:


    // 0: load flags
    // 1: use renderer
    // 2: render mode
    typedef tuple<FT_Int32, bool, FT_Render_Mode>  ModeTuple;


    FT_Long  num_used_glyphs = -1;

    vector<pair<FT_Matrix*, FT_Vector*>>  transformations;
    vector<ModeTuple>                     modes;
  };


#endif // VISITORS_FACE_VISITOR_LOAD_GLYPHS_H_
