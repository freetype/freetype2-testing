// CacheFuzzTarget.h
//
//   Base class of cache fuzz targets.
//
// Copyright 2024 by
// The FreeType Project.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_CACHEFUZZTARGET_H_
#define TARGETS_CACHEFUZZTARGET_H_


#include "targets/FuzzTarget.h"

#include <ft2build.h>
#include FT_CACHE_H

namespace freetype {

  class CacheFuzzTarget
    : public FuzzTarget
  {
  public:

    void
    run( const uint8_t*  data,
         size_t          size ) override;

  private:

    static FT_Error
    face_requester( FTC_FaceID  face_id,
                    FT_Library  library,
                    FT_Pointer  req_data,
                    FT_Face*    aface );
  };
}


#endif // TARGETS_CACHEFUZZTARGET_H_
