// truetype.cpp
//
//   Implementation of TrueTypeFuzzTarget.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/font-drivers/truetype.h"

#include "iterators/faceloaditerator.h"
#include "iterators/faceprepiterator-bitmaps.h"
#include "iterators/faceprepiterator-multiplemasters.h"
#include "iterators/faceprepiterator-outlines.h"
#include "visitors/facevisitor-charcodes.h"
#include "visitors/facevisitor-gasp.h"
#include "visitors/facevisitor-kerning.h"
#include "visitors/facevisitor-multiplemasters.h"
#include "visitors/facevisitor-sfntnames.h"
#include "visitors/facevisitor-truetypepatents.h"
#include "visitors/facevisitor-truetypetables.h"
#include "visitors/facevisitor-variants.h"


  using namespace std;


  TrueTypeFuzzTarget::
  TrueTypeFuzzTarget( void )
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
                       FaceLoader::FontFormat::TRUETYPE) );

    // -----------------------------------------------------------------------
    // Face load iterators:

    (void) fli->set_supported_font_format( FaceLoader::FontFormat::TRUETYPE );

    (void) fli->add_iterator( move( fpi_bitmaps  ) );
    (void) fli->add_iterator( move( fpi_outlines ) );
    (void) fli->add_iterator( move( fpi_mm       ) );

    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorCharCodes>() );
    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorGasp>() );
    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorSfntNames>() );
    (void) fli
      ->add_once_visitor(
        fuzzing::make_unique<FaceVisitorTrueTypePatents>() );
    (void) fli
      ->add_once_visitor(
        fuzzing::make_unique<FaceVisitorTrueTypeTables>() );
    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorVariants>() );
    
    // -----------------------------------------------------------------------
    // Fuzz target:

    (void) set_iterator( move( fli ) );
  }
