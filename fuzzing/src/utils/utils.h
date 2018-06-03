// utils.h
//
//   Collection of globally useful snippets.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_


#define WARN_ABOUT_IGNORED_VALUES( available, capped, name )  \
  do                                                          \
  {                                                           \
    LOG_IF( WARNING, (available) > (capped) )                 \
      << "aborted early: "                                    \
      << ( (available) - (capped) )                           \
      << " " << name << " ignored";                           \
  } while (0)


#include <memory>

#include <archive.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H


  using namespace std;

  namespace fuzzing
  {

    typedef unique_ptr<struct archive,
      decltype( archive_read_free )*>  Unique_Archive;

    typedef unique_ptr<FT_FaceRec,
      decltype( FT_Done_Face )*>  Unique_FT_Face;

    typedef unique_ptr<FT_GlyphRec,
      decltype( FT_Done_Glyph )*>  Unique_FT_Glyph;


    Unique_FT_Face
    make_unique_face( FT_Face  face=nullptr );


    Unique_FT_Glyph
    make_unique_glyph( FT_Glyph  glyph=nullptr );


    // @Description:
    //   As of today (Summer 2018), `std::make_unique' is still not reliably
    //   available.  This version of `make_unique' helps to bridge the gap
    //   since the usefulness of `make_unique' is undisputed.
    //   Source: https://isocpp.org/files/papers/N3656.txt

    template<typename T, typename... Args>
    std::unique_ptr<T>
    make_unique( Args&&...  args )
    {
      return std::unique_ptr<T>( new T( std::forward<Args>( args )... ) );
    }
  }


#endif // UTILS_UTILS_H_
