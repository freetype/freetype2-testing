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


#include "targets/base.h"

#include <cassert>
#include <iostream>

#include <ft2build.h>
#include FT_AUTOHINTER_H
#include FT_MODULE_H

#include "utils/logging.h"


  const FT_UInt  FuzzTarget::HINTING_ADOBE    = FT_HINTING_ADOBE;
  const FT_UInt  FuzzTarget::HINTING_FREETYPE = FT_HINTING_FREETYPE;


  FuzzTarget::
  FuzzTarget( void )
  {
    FT_Error  error;

    FT_Int  major;
    FT_Int  minor;
    FT_Int  patch;

    
    error = FT_Init_FreeType( &library );
    LOG_FT_ERROR( "FT_Init_FreeType", error );

    if ( error != 0 )
      return;

    (void) FT_Library_Version( library, &major, &minor, &patch );
    LOG( INFO ) << "using FreeType " << major << "." << minor << "." << patch;
  }


  FuzzTarget::
  ~FuzzTarget( void )
  {
    (void) FT_Done_FreeType( library );
    library = nullptr;
  }


  void
  FuzzTarget::
  run( const uint8_t*  data,
       size_t          size )
  {
    if ( size < 1 )
      return;

    assert( face_load_iterator != nullptr );

    (void) face_load_iterator->set_library( library );
    (void) face_load_iterator->set_raw_bytes( data, size );
    (void) face_load_iterator->run();
  }


  void
  FuzzTarget::
  set_supported_font_format( FaceLoader::FontFormat  format )
  {
    assert( face_load_iterator != nullptr );
    (void) face_load_iterator->set_supported_font_format( format );
  }


  void
  FuzzTarget::
  set_data_is_tar_archive( bool  is_tar_archive )
  {
    assert( face_load_iterator != nullptr );
    (void) face_load_iterator->set_data_is_tar_archive( is_tar_archive );
  }


  bool
  FuzzTarget::
  set_property( const string  module_name,
                const string  property_name,
                const void*   value )
  {
    FT_Error  error;


    LOG( INFO ) << "setting '" << property_name
                << "' in '"   << module_name << "'";

    error = FT_Property_Set( library,
                             module_name.c_str(),
                             property_name.c_str(),
                             value );

    LOG_FT_ERROR( "FT_Property_Set", error );

    return error == 0 ? true : false;
  }


  unique_ptr<FaceLoadIterator>&
  FuzzTarget::
  set_iterator( unique_ptr<FaceLoadIterator>  iterator )
  {
    face_load_iterator = move( iterator );
    return face_load_iterator;
  }
