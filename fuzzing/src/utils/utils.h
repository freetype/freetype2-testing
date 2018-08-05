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


    // Description:
    //   Creates a copy of a glyph.
    //
    // Input:
    //   glyph ::
    //     A glyph that will be copied.
    //
    // Return:
    //   A freshly created copy of the glyph.

    Unique_FT_Glyph
    copy_unique_glyph( const Unique_FT_Glyph&  glyph );


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


    // @Description:
    //    Extract a loaded glyph from the face.
    //
    // @Input:
    //   face ::
    //     A face that has a loaded glyph.
    //
    // @Return:
    //   The last loaded glyph of the input face.

    Unique_FT_Glyph
    get_glyph_from_face( const Unique_FT_Face&  face );


    // @Description:
    //   Get the amount of pixels that glyph's bitmap uses.  This can also
    //   be applied to outline glyphs which have not been rendered yet.
    //
    // @Input:
    //   glyph ::
    //     A glyph.
    //
    // @Return:
    //   The amount of pixels of the glyphs's bitmap.

    FT_Pos
    get_glyph_pixels( const Unique_FT_Glyph&  glyph );


    // @Description:
    //   Check if the given glyph's bitmap exceeds a certain amount of pixels.
    //
    // @Input:
    //   glyph ::
    //     A glpyh that is to be evaluated.
    //
    //   reasonable_size ::
    //     Amount of pixels.
    //
    // @Return:
    //    `true', if the given glyph's bitmap has less than or equally many
    //    pixels as the reasonable size.

    bool
    glyph_has_reasonable_size( const Unique_FT_Glyph&  glyph,
                               FT_Pos                  reasonable_size );


    // @Description:
    //   Check the size of the glyph and evaluate if it is worth working with
    //   it.  This function logs all relevant details like glyph size and
    //   success validity.
    //
    // @Input:
    //   glyph ::
    //     A glpyh that is to be evaluated.
    //
    // @Return:
    //   `true', if `fuzzing::get_glyph_pixels()' is below a reasonale
    //   threshold, `false' if it is above it.

    bool
    glyph_has_reasonable_work_size( const Unique_FT_Glyph&  glyph );


    // @Description:
    //   Check the size of the glyph and evaluate if it is worth rendering it
    //   This function logs all relevant details like glyph size and success
    //   validity.
    //
    // @Input:
    //   glyph ::
    //     A glpyh that is to be evaluated.
    //
    // @Return:
    //   `true', if `fuzzing::get_glyph_pixels()' is below a reasonale
    //   threshold, `false' if it is above it.

    bool
    glyph_has_reasonable_render_size( const Unique_FT_Glyph&  glyph );
  }


#endif // UTILS_UTILS_H_
