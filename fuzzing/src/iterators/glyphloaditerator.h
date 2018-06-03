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

    
  protected:


    FT_Int32  load_flags = FT_LOAD_DEFAULT;

    vector<unique_ptr<GlyphVisitor>>  glyph_visitors;
  };


#endif // ITERATORS_GLYPH_LOAD_ITERATOR_H_
