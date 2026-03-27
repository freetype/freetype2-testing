// GzipFuzzTarget.cpp
//
//   Implementation of GzipFuzzTarget.
//
// Copyright 2019 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/support/GzipFuzzTarget.h"

#include FT_GZIP_H

#include "utils/FreeTypeStream.h"
#include "utils/logging.h"


  void
  freetype::GzipFuzzTarget::
  run( const uint8_t*  data,
       size_t          size )
  {
    FreeTypeStream  compressed( get_ft_memory(), data, size );
    FreeTypeStream  uncompressed;
    FT_Error        error;


    error = FT_Stream_OpenGzip( uncompressed.get(), compressed.get() );
    LOG_FT_ERROR( "FT_Stream_OpenGzip", error );

    if ( error != 0 )
      return;

    (void) uncompressed.read_forwards();
    (void) uncompressed.read_backwards();

    // Fuzz FT_Gzip_Uncompress
    FT_ULong  uncompressed_size = (FT_ULong)size * 4; // Arbitrary guess
    FT_Byte*  buffer = (FT_Byte*)malloc( uncompressed_size );
    if ( buffer ) {
      (void) FT_Gzip_Uncompress( get_ft_memory(), buffer, &uncompressed_size, data, (FT_ULong)size );
      free( buffer );
    }
  }
