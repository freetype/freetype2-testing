// cidtype1.cpp
//
//   Implementation of CidType1FuzzTarget.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/font-drivers/cidtype1.h"

#include <glog/logging.h>

#include "iterators/faceloaditerator.h"
#include "iterators/faceprepiterator-bitmaps.h"
#include "iterators/faceprepiterator-outlines.h"
#include "iterators/glyphloaditerator-naive.h"
#include "visitors/facevisitor-cid.h"
#include "visitors/facevisitor-charcodes.h"
#include "visitors/facevisitor-type1tables.h"
#include "visitors/facevisitor-variants.h"
#include "visitors/glyphvisitor-cbox.h"
#include "visitors/glyphvisitor-transform.h"


  using namespace std;


  CidType1FuzzTarget::
  CidType1FuzzTarget( void )
  {
    auto  fli = fuzzing::make_unique<FaceLoadIterator>();

    auto  fpi_bitmaps  = fuzzing::make_unique<FacePrepIteratorBitmaps>();
    auto  fpi_outlines = fuzzing::make_unique<FacePrepIteratorOutlines>();

    auto  gli_bitmaps  = fuzzing::make_unique<GlyphLoadIteratorNaive>();
    auto  gli_outlines = fuzzing::make_unique<GlyphLoadIteratorNaive>();


    // -----------------------------------------------------------------------
    // Glyph load iterators:
    
    (void) gli_bitmaps ->add_load_flags( FT_LOAD_COLOR     );
    (void) gli_outlines->add_load_flags( FT_LOAD_NO_BITMAP );

    (void) gli_bitmaps
      ->add_visitor( fuzzing::make_unique<GlyphVisitorCBox>() );
    
    (void) gli_outlines
      ->add_visitor( fuzzing::make_unique<GlyphVisitorCBox>() );
    (void) gli_outlines
      ->add_visitor( fuzzing::make_unique<GlyphVisitorTransform>() );

    // -----------------------------------------------------------------------
    // Face preparation iterators:

    (void) fpi_bitmaps ->add_iterator( move( gli_bitmaps  ) );
    (void) fpi_outlines->add_iterator( move( gli_outlines ) );

    // -----------------------------------------------------------------------
    // Face load iterators:

    (void) fli
      ->set_supported_font_format( FaceLoader::FontFormat::CID_TYPE_1 );

    (void) fli->add_iterator( move( fpi_bitmaps  ) );
    (void) fli->add_iterator( move( fpi_outlines ) );

    (void) fli->add_once_visitor( fuzzing::make_unique<FaceVisitorCid>() );
    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorCharCodes>() );
    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorVariants>() );

    (void) fli
      ->add_always_visitor( fuzzing::make_unique<FaceVisitorType1Tables>() );

    // -----------------------------------------------------------------------
    // Fuzz target:

    (void) set_iterator( move ( fli ) );
  }
