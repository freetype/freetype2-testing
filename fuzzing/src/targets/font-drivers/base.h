// base.h
//
//   Base class of fuzz targets that are specifically built to fuzz font
//   drivers.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_BASE_H_
#define TARGETS_FONT_DRIVERS_BASE_H_


#include <cstdint>
#include <functional>
#include <string>

#include <ft2build.h>
#include FT_AUTOHINTER_H
#include FT_FREETYPE_H
#include FT_MODULE_H

#include "iterators/faceloaditerator.h"
#include "iterators/faceprepiterator.h"
#include "iterators/glyphloaditerator.h"
#include "utils/faceloader.h"
#include "utils/utils.h"
#include "visitors/facevisitor.h"


  using namespace std;


  class FontDriverFuzzTarget
  {
  public:


    FontDriverFuzzTarget( void );


    FontDriverFuzzTarget( const FontDriverFuzzTarget& ) = delete;
    FontDriverFuzzTarget& operator= ( const FontDriverFuzzTarget& ) = delete;


    virtual
    ~FontDriverFuzzTarget( void );


    // @Input:
    //   data ::
    //     Fuzzed input data.
    //
    //   size ::
    //     The size of fuzzed input data.

    void
    run( const uint8_t*  data,
         size_t          size );


  protected:


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


#endif // TARGETS_FONT_DRIVERS_BASE_H_