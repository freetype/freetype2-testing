// faceprepiterator-bitmaps.h
//
//   Iterator that prepares faces for bitmap usage.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef ITERATORS_FACE_PREP_ITERATOR_BITMAPS_H_
#define ITERATORS_FACE_PREP_ITERATOR_BITMAPS_H_


#include <vector>

#include "iterators/faceprepiterator.h"


  using namespace fuzzing;
  using namespace std;


  class FacePrepIteratorBitmaps
  : public FacePrepIterator
  {
  public:


    FacePrepIteratorBitmaps( void ) {}
    

    FacePrepIteratorBitmaps(
      const FacePrepIteratorBitmaps& ) = delete;
    FacePrepIteratorBitmaps& operator= (
      const FacePrepIteratorBitmaps& ) = delete;


    virtual
    ~FacePrepIteratorBitmaps( void ) {}


    void
    run( const unique_ptr<FaceLoader>&  face_loader )
    override;


  private:


    static const FT_Int  STRIKE_INDEX_MAX = 10;


    Unique_FT_Face
    get_prepared_face( const unique_ptr<FaceLoader>&  face_loader,
                       FT_Int                         index );
  };


#endif // ITERATORS_FACE_PREP_ITERATOR_BITMAPS_H_
