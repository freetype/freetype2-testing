// FuzzTarget.h
//
//   Base class of fuzz targets.
//
// Copyright 2019 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_SUPPORT_FUZZTARGET_H_
#define TARGETS_SUPPORT_FUZZTARGET_H_


#include <cstdint>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/internal/internal.h>
#include FT_INTERNAL_OBJECTS_H


namespace freetype {

  class FuzzTarget
  {
  public:


    FuzzTarget( const FuzzTarget& ) = delete;
    FuzzTarget& operator= ( const FuzzTarget& ) = delete;


    ~FuzzTarget();


    virtual void
    run( const uint8_t*  data,
         size_t          size ) = 0;


  protected:


    FuzzTarget();


    FT_Library
    get_ft_library()
    {
      return library;
    }


    FT_Memory
    get_ft_memory()
    {
      return library->memory;
    }


  private:


    FT_Library  library = nullptr;
  };
}


#endif // TARGETS_SUPPORT_FUZZTARGET_H_
