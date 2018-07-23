// base.h
//
//   Base class of fuzz targets.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_BASE_H_
#define TARGETS_BASE_H_


#include <cstdint>
#include <functional>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "iterators/faceloaditerator.h"
#include "iterators/faceprepiterator.h"
#include "iterators/glyphloaditerator.h"
#include "utils/faceloader.h"
#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace std;


  class FuzzTarget
  {
  public:


    FuzzTarget( void );


    FuzzTarget( const FuzzTarget& ) = delete;
    FuzzTarget& operator= ( const FuzzTarget& ) = delete;


    virtual
    ~FuzzTarget( void );


    // @Description:
    //   Run some input on the fuzz target.
    //
    // @Input:
    //   data ::
    //     Fuzzed input data.
    //
    //   size ::
    //     The size of fuzzed input data.

    virtual void
    run( const uint8_t*  data,
         size_t          size );


  protected:


    // @See: FaceLoader::set_data_is_tar_archive()

    void
    set_data_is_tar_archive( bool  is_tar_archive );


    // @Description:
    //   Set a FreeType property via `FT_Property_Set'.
    //
    // @Input:
    //   module_name ::
    //     See `FT_Property_Set'.
    //
    //   property_name ::
    //     See `FT_Property_Set'.
    //
    //   value ::
    //     See `FT_Property_Set'.
    //
    // @Return:
    //   `false' if `FT_Property_Set' returns an error, 'true' otherwise.

    bool
    set_property( string  module_name,
                  string  property_name,
                  void*   value );


    // @Description:
    //   Set the face load iterator for this fuzz target.  This function
    //   overwrites other iterators that have been set before.
    //
    // @Input:
    //   iterator ::
    //     An face load iterator that will be used by `run()'.
    //
    // @Return:
    //   A reference to the added iterator.
    
    unique_ptr<FaceLoadIterator>&
    set_iterator( unique_ptr<FaceLoadIterator>  iterator );


  private:


    FT_Library  library;

    unique_ptr<FaceLoadIterator>  face_load_iterator;
  };


#endif // TARGETS_BASE_H_
