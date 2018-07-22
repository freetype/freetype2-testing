// type1.cpp
//
//   Implementation of Type1FuzzTarget.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/font-drivers/type1.h"

#include "iterators/faceloaditerator.h"
#include "iterators/faceprepiterator-bitmaps.h"
#include "iterators/faceprepiterator-multiplemasters.h"
#include "iterators/faceprepiterator-outlines.h"
#include "iterators/glyphloaditerator-naive.h"
#include "visitors/facevisitor-charcodes.h"
#include "visitors/facevisitor-kerning.h"
#include "visitors/facevisitor-multiplemasters.h"
#include "visitors/facevisitor-trackkerning.h"
#include "visitors/facevisitor-type1tables.h"
#include "visitors/facevisitor-variants.h"


  using namespace std;


  Type1FuzzTarget::
  Type1FuzzTarget( void )
  {
    auto  fli = fuzzing::make_unique<FaceLoadIterator>();

    auto  fpi_bitmaps  = fuzzing::make_unique<FacePrepIteratorBitmaps>();
    auto  fpi_outlines = fuzzing::make_unique<FacePrepIteratorOutlines>();
    auto  fpi_mm =
      fuzzing::make_unique<FacePrepIteratorMultipleMasters>();


    // -----------------------------------------------------------------------
    // Face preparation iterators:

    (void) fpi_bitmaps
      ->add_visitor( fuzzing::make_unique<FaceVisitorKerning>() );
    (void) fpi_outlines
      ->add_visitor( fuzzing::make_unique<FaceVisitorKerning>() );
    
    (void) fpi_outlines
      ->add_visitor( fuzzing::make_unique<FaceVisitorMultipleMasters>(
                       FaceLoader::FontFormat::TYPE_1) );

    (void) fpi_mm
      ->add_visitor( fuzzing::make_unique<FaceVisitorType1Tables>() );

    // -----------------------------------------------------------------------
    // Face load iterators:

    (void) fli->set_supported_font_format( FaceLoader::FontFormat::TYPE_1 );

    // TODO: activate as soon as the `libarchive' mem leak is figured out.
    // (void) fli->set_accept_tar_archives( true );

    (void) fli->add_iterator( move( fpi_bitmaps  ) );
    (void) fli->add_iterator( move( fpi_outlines ) );
    (void) fli->add_iterator( move( fpi_mm       ) );

    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorCharCodes>() );
    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorVariants>() );

    (void) fli
      ->add_always_visitor( fuzzing::make_unique<FaceVisitorTrackKerning>() );
    (void) fli
      ->add_always_visitor( fuzzing::make_unique<FaceVisitorType1Tables>() );
    
    // -----------------------------------------------------------------------
    // Fuzz target:

    (void) set_iterator( move( fli ) );
  }
