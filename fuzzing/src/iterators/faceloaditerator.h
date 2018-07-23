// faceloaditerator.h
//
//   Base class of iterators over faces.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef ITERATORS_FACE_LOAD_ITERATOR_H_
#define ITERATORS_FACE_LOAD_ITERATOR_H_


#include "iterators/faceprepiterator.h"
#include "utils/faceloader.h"
#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace fuzzing;
  using namespace std;


  class FaceLoadIterator
  {
  public:

    
    FaceLoadIterator( void )
      : face_loader( new FaceLoader ) {}


    FaceLoadIterator( const FaceLoadIterator& ) = delete;
    FaceLoadIterator& operator= ( const FaceLoadIterator& ) = delete;


    // @See: FaceLoader::set_supported_font_format

    void
    set_supported_font_format( FaceLoader::FontFormat  format );


    // @See: FaceLoader::set_library

    void
    set_library( FT_Library  library );


    // @See: FaceLoader::set_raw_bytes

    void
    set_raw_bytes( const uint8_t*  data,
                   size_t          size );


    // @See: FaceLoader::set_data_is_tar_archive()

    void
    set_data_is_tar_archive( bool  is_tar_archive );
    

    // @Description:
    //   Add a face visitor that is called once, with the first loaded face.
    //
    // @Input:
    //   visitor ::
    //     A face visitor.

    void
    add_once_visitor( unique_ptr<FaceVisitor>  visitor );


    // @Description:
    //   Add a face visitor that is called with every loaded face.
    //
    // @Input:
    //   visitor ::
    //     A face visitor.

    void
    add_always_visitor( unique_ptr<FaceVisitor>  visitor );


    // @Description:
    //   Add a face preparation iterator that is called with every loaded
    //   face.
    //
    // @Input:
    //   iterator ::
    //     A face preparation iterator.

    void
    add_iterator( unique_ptr<FacePrepIterator>  iterator );


    // @Description:
    //   Iterate over every font + instance and call all subiterators and
    //   visitors.

    void
    run( void );


  private:


    static const FT_Long  FACE_INDEX_MAX     = 20;
    static const FT_Long  INSTANCE_INDEX_MAX =  5;

    unique_ptr<FaceLoader>  face_loader;

    vector<unique_ptr<FaceVisitor>>  once_face_visitors;
    vector<unique_ptr<FaceVisitor>>  always_face_visitors;

    vector<unique_ptr<FacePrepIterator>>  face_prep_iterators;
  };


#endif // ITERATORS_FACE_LOAD_ITERATOR_H_
