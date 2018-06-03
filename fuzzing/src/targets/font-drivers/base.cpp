// base.cpp
//
//   Implementation of FontDriverFuzzTarget.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/font-drivers/base.h"

#include <cassert>
#include <iostream>

#include <glog/logging.h>


  FontDriverFuzzTarget::
  FontDriverFuzzTarget( void )
  {
    FT_Error  error;

    FT_Int  major;
    FT_Int  minor;
    FT_Int  patch;
    
    unsigned int  hinting_engine;

    
    error = FT_Init_FreeType( &library );
    if ( error != 0 )
    {
      LOG( ERROR ) << "FT_Init_FreeType failed: " << error;
      return;
    }

    (void) FT_Library_Version( library, &major, &minor, &patch );
    LOG( INFO ) << "using FreeType " << major << "." << minor << "." << patch;

    // TODO: move this away from here ...
    hinting_engine = FT_HINTING_ADOBE;
    (void) FT_Property_Set( library,
                            "cff",
                            "hinting-engine",
                            &hinting_engine );
  }


  FontDriverFuzzTarget::
  ~FontDriverFuzzTarget( void )
  {
    (void) FT_Done_FreeType( library );
    library = nullptr;
  }


  void
  FontDriverFuzzTarget::
  run( const uint8_t*  data,
       size_t          size )
  {
    if ( size < 1)
      return;

    assert( face_load_iterator != nullptr );

    (void) face_load_iterator->set_library( library );
    (void) face_load_iterator->set_raw_bytes( data, size );
    (void) face_load_iterator->run();
  }


  unique_ptr<FaceLoadIterator>&
  FontDriverFuzzTarget::
  set_iterator( unique_ptr<FaceLoadIterator>  iterator )
  {
    face_load_iterator = move( iterator );
    return face_load_iterator;
  }
