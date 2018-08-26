// facevisitor-bdf.cpp
//
//   Implementation of FaceVisitorBdf.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "visitors/facevisitor-bdf.h"

#include <cassert>

#include <ft2build.h>
#include FT_BDF_H

#include "utils/logging.h"


  FaceVisitorBdf::
  FaceVisitorBdf( FaceLoader::FontFormat  format )
  {
    font_format = format;
  }


  void
  FaceVisitorBdf::
  run( Unique_FT_Face  face )
  {
    FT_Error     error;
    const char*  charset_encoding;
    const char*  charset_registry;
      

    assert( face != nullptr );

    if ( font_format == FaceLoader::FontFormat::BDF )
    {
      error = FT_Get_BDF_Charset_ID( face.get(),
                                     &charset_encoding,
                                     &charset_registry );
      LOG_FT_ERROR( "FT_Get_BDF_Charset_ID", error );

      if ( error == 0 )
      {
        LOG( INFO ) << "BDF charset encoding: " << string( charset_encoding );
        LOG( INFO ) << "BDF charset registry: " << string( charset_registry );
      }
    }
  }
