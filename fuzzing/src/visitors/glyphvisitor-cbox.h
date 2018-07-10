// glyphvisitor-cbox.h
//
//   Query glyphs' control boxes.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef VISITORS_GLYPH_VISITOR_CBOX_H_
#define VISITORS_GLYPH_VISITOR_CBOX_H_


#include "visitors/glyphvisitor.h"


  using namespace std;


  class GlyphVisitorCBox
  : public GlyphVisitor
  {
  public:


    GlyphVisitorCBox( void ) {}


    GlyphVisitorCBox( const GlyphVisitorCBox& ) = delete;
    GlyphVisitorCBox& operator= ( const GlyphVisitorCBox& ) = delete;


    virtual
    ~GlyphVisitorCBox( void ) {}


    void
    run( Unique_FT_Glyph  glyph )
    override;


  private:


    void
    query_cbox( const Unique_FT_Glyph&  glyph,
                FT_Glyph_BBox_Mode      bbox_mode,
                const string&           name );
  };


#endif // VISITORS_GLYPH_VISITOR_CBOX_H_
