// faceprepiterator.h
//
//   Base class of iterators that prepare faces.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef ITERATORS_FACE_PREP_ITERATOR_H_
#define ITERATORS_FACE_PREP_ITERATOR_H_


#include "iterators/glyphloaditerator.h"
#include "utils/faceloader.h"
#include "utils/utils.h"
#include "visitors/facevisitor.h"


  class FacePrepIterator
  {
  public:


    FacePrepIterator( void ) {}


    FacePrepIterator( const FacePrepIterator& ) = delete;
    FacePrepIterator& operator= ( const FacePrepIterator& ) = delete;


    virtual
    ~FacePrepIterator( void ) {}


    // @Description:
    //   Add a face visitor that is called with every prepared face.
    //
    // @Input:
    //   visitor ::
    //     A face visitor.
    //
    // @Return:
    //   A reference to the added visitor.

    void
    add_visitor( unique_ptr<FaceVisitor>  visitor );


    // @Description:
    //   Add a glyph load iterator that is called with every prepared face.
    //
    // @Input:
    //   iterator ::
    //     A face preparation iterator.
    //
    // @Return:
    //   A reference to the added iterator.

    void
    add_iterator( unique_ptr<GlyphLoadIterator>  iterator );


    virtual void
    run( const unique_ptr<FaceLoader>&  face_loader ) = 0;


  protected:


    vector<unique_ptr<FaceVisitor>>        face_visitors;
    vector<unique_ptr<GlyphLoadIterator>>  glyph_load_iterators;
  };


#endif // ITERATORS_FACE_PREP_ITERATOR_H_
