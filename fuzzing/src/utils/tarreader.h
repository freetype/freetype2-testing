// tarreader.h
//
//   Used to extract files from tar archives.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef UTILS_TAR_READER_H_
#define UTILS_TAR_READER_H_

#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "utils/utils.h"


  using namespace std;


  class TarReader
  {
  public:


    // @Input:
    //   files ::
    //     Extracted files will be added to this vector.
    TarReader( vector<vector<FT_Byte>>&  files )
      : files(files) {}


    TarReader( const TarReader& ) = delete;
    TarReader& operator= ( const TarReader& ) = delete;


    bool
    extract_data( const uint8_t*  data,
                  size_t          size );


  private:


    vector<vector<FT_Byte>>&  files;
  };


#endif // UTILS_TAR_READER_H_
