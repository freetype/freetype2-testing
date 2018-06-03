// faceprepiterator-multiplemasters.h
//
//   Iterator that prepares faces for outline usage with multiple masters.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef ITERATORS_FACE_PREP_ITERATOR_MULTIPLE_MASTERS_H_
#define ITERATORS_FACE_PREP_ITERATOR_MULTIPLE_MASTERS_H_


#include <vector>

#include <ft2build.h>
#include FT_MULTIPLE_MASTERS_H

#include "iterators/faceprepiterator-outlines.h"


  using namespace std;


  class FacePrepIteratorMultipleMasters
  : public FacePrepIteratorOutlines
  {
  public:


    FacePrepIteratorMultipleMasters( void ) {}
    

    FacePrepIteratorMultipleMasters(
      const FacePrepIteratorMultipleMasters& ) = delete;
    FacePrepIteratorMultipleMasters& operator= (
      const FacePrepIteratorMultipleMasters& ) = delete;


    virtual
    ~FacePrepIteratorMultipleMasters( void ) {}


  protected:


    virtual Unique_FT_Face
    get_prepared_face( const unique_ptr<FaceLoader>&     face_loader,
                       vector<CharSizeTuple>::size_type  index )
    override;


  private:


    Unique_FT_Face
    free_and_return( FT_Library      library,
                     FT_MM_Var*      master,
                     Unique_FT_Face  face );
  };


#endif // ITERATORS_FACE_PREP_ITERATOR_MULTIPLE_MASTERS_H_
