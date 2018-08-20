// bitmaps.cpp
//
//   Implementation of GlyphsBitmapsFuzzTarget.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/glyphs/bitmaps.h"

#include "iterators/faceloaditerator.h"
#include "iterators/faceprepiterator-bitmaps.h"
#include "iterators/glyphloaditerator-naive.h"
#include "visitors/glyphvisitor-bitmap-handling.h"
#include "utils/logging.h"


  const FT_Long  GlyphsBitmapsFuzzTarget::NUM_LOAD_GLYPHS = 20;


  GlyphsBitmapsFuzzTarget::
  GlyphsBitmapsFuzzTarget( void )
  {
    auto  fli = fuzzing::make_unique<FaceLoadIterator>();
    auto  fpi = fuzzing::make_unique<FacePrepIteratorBitmaps>();
    auto  gli =
      fuzzing::make_unique<GlyphLoadIteratorNaive>( NUM_LOAD_GLYPHS );


    // -----------------------------------------------------------------------
    // Glyph load iterators:

    (void) gli
      ->add_visitor( fuzzing::make_unique<GlyphVisitorBitmapHandling>() );

    // -----------------------------------------------------------------------
    // Assemble the rest:

    (void) fpi->add_iterator( move( gli ) );

    (void) fli->add_iterator( move( fpi ) );

    // -----------------------------------------------------------------------
    // Fuzz target:

    (void) set_iterator( move( fli ) );
  }
