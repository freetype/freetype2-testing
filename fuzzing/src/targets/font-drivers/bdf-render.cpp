// bdf-render.cpp
//
//   Implementation of BdfRenderFuzzTarget.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/font-drivers/bdf-render.h"

#include "iterators/faceloaditerator.h"
#include "iterators/faceprepiterator-bitmaps.h"
#include "visitors/facevisitor-loadglyphs-bitmaps.h"


  using namespace std;


  const FT_Long  BdfRenderFuzzTarget::NUM_USED_BITMAPS = 30;


  BdfRenderFuzzTarget::
  BdfRenderFuzzTarget( void )
  {
    auto  fli          = fuzzing::make_unique<FaceLoadIterator>();
    auto  fpi_bitmaps  = fuzzing::make_unique<FacePrepIteratorBitmaps>();


    // -----------------------------------------------------------------------
    // Face preparation iterator:

    (void) fpi_bitmaps
      ->add_visitor(
        fuzzing::make_unique<FaceVisitorLoadGlyphsBitmaps>(
          NUM_USED_BITMAPS ) );

    // -----------------------------------------------------------------------
    // Face load iterator:

    (void) fli->set_supported_font_format( FaceLoader::FontFormat::BDF );
    
    (void) fli->add_iterator( move( fpi_bitmaps ) );

    // -----------------------------------------------------------------------
    // Fuzz target:

    (void) set_iterator( move( fli ) );
  }
