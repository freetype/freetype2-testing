// cff.cpp
//
//   Implementation of CffFuzzTarget.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/font-drivers/cff.h"

#include <glog/logging.h>

#include "iterators/faceloaditerator.h"
#include "iterators/faceprepiterator-bitmaps.h"
#include "iterators/faceprepiterator-multiplemasters.h"
#include "iterators/faceprepiterator-outlines.h"
#include "iterators/glyphloaditerator-naive.h"
#include "visitors/facevisitor-cid.h"
#include "visitors/facevisitor-charcodes.h"
#include "visitors/facevisitor-kerning.h"
#include "visitors/facevisitor-multiplemasters.h"
#include "visitors/facevisitor-truetypetables.h"
#include "visitors/facevisitor-variants.h"
#include "visitors/glyphvisitor-transform.h"


  using namespace std;


  CffFuzzTarget::
  CffFuzzTarget( void )
  {
    auto  fli = fuzzing::make_unique<FaceLoadIterator>();

    auto  fpi_bitmaps  = fuzzing::make_unique<FacePrepIteratorBitmaps>();
    auto  fpi_outlines = fuzzing::make_unique<FacePrepIteratorOutlines>();
    auto  fpi_mm =
      fuzzing::make_unique<FacePrepIteratorMultipleMasters>();

    auto  gli_bitmaps  = fuzzing::make_unique<GlyphLoadIteratorNaive>();
    auto  gli_outlines = fuzzing::make_unique<GlyphLoadIteratorNaive>();
    auto  gli_mm       = fuzzing::make_unique<GlyphLoadIteratorNaive>();


    // -----------------------------------------------------------------------
    // Glyph load iterators:

    (void) gli_bitmaps ->add_load_flags( FT_LOAD_COLOR     );
    (void) gli_outlines->add_load_flags( FT_LOAD_NO_BITMAP );
    (void) gli_mm      ->add_load_flags( FT_LOAD_NO_BITMAP );

    (void) gli_outlines
      ->add_visitor( fuzzing::make_unique<GlyphVisitorTransform>() );

    // -----------------------------------------------------------------------
    // Face preparation iterators:

    (void) fpi_bitmaps ->add_iterator( move( gli_bitmaps  ) );
    (void) fpi_outlines->add_iterator( move( gli_outlines ) );
    (void) fpi_mm      ->add_iterator( move( gli_mm       ) );

    (void) fpi_bitmaps
      ->add_visitor( fuzzing::make_unique<FaceVisitorKerning>() );
    (void) fpi_outlines
      ->add_visitor( fuzzing::make_unique<FaceVisitorKerning>() );

    (void) fpi_outlines
      ->add_visitor( fuzzing::make_unique<FaceVisitorMultipleMasters>() );

    // -----------------------------------------------------------------------
    // Face load iterators:

    (void) fli->set_supported_font_format( FaceLoader::FontFormat::CFF );
    
    (void) fli->add_iterator( move ( fpi_bitmaps  ) );
    (void) fli->add_iterator( move ( fpi_outlines ) );
    (void) fli->add_iterator( move ( fpi_mm       ) );
    
    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorCharCodes>() );
    (void) fli->add_once_visitor( fuzzing::make_unique<FaceVisitorCid>() );
    (void) fli
      ->add_once_visitor(
        fuzzing::make_unique<FaceVisitorTrueTypeTables>() );
    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorVariants>() );

    // -----------------------------------------------------------------------
    // Fuzz target:

    (void) set_iterator( move ( fli ) );
  }
