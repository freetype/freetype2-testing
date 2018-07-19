// glyphloaditerator.h
//
//   Base class of iterators over glyphs.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef ITERATORS_GLYPH_LOAD_ITERATOR_H_
#define ITERATORS_GLYPH_LOAD_ITERATOR_H_

#include <vector>

#include "iterators/glyphrenderiterator.h"
#include "utils/utils.h"
#include "visitors/glyphvisitor.h"


  using namespace std;


  class GlyphLoadIterator
  {
  public:


    GlyphLoadIterator( void ) {}


    GlyphLoadIterator( const GlyphLoadIterator& ) = delete;
    GlyphLoadIterator& operator= ( const GlyphLoadIterator& ) = delete;


    virtual
    ~GlyphLoadIterator( void ) {}


    virtual void
    run( Unique_FT_Face  face ) = 0;


    void
    add_load_flags( FT_Int32  flags );


    // @Description:
    //   Add a glpyh visitor that is called with every loaded glyph.
    //
    // @Input:
    //   visitor ::
    //     A glyph visitor.
    //
    // @Return:
    //   A reference to the added visitor.

    void
    add_visitor( unique_ptr<GlyphVisitor>  visitor );


    // @Description:
    //   Add a glyph render iterator that is called with every loaded glyph.
    //
    // @Input:
    //   iterator ::
    //     A glyph render iterator.
    //
    // @Return:
    //   A reference to the added iterator.

    void
    add_iterator( unique_ptr<GlyphRenderIterator>  iterator );

    
  protected:


    FT_Int32  load_flags = FT_LOAD_DEFAULT;

    vector<unique_ptr<GlyphVisitor>>         glyph_visitors;
    vector<unique_ptr<GlyphRenderIterator>>  glyph_render_iterators;


    // @Description:
    //   Invoke all visitors and iterators with a copy of the glyph.
    //
    // @Input:
    //   glyph ::
    //     Basic glyph that will be copied for every visitor and every
    //     iterator.

    void
    invoke_visitors_and_iterators( const Unique_FT_Glyph&  glyph );
  };


#endif // ITERATORS_GLYPH_LOAD_ITERATOR_H_
