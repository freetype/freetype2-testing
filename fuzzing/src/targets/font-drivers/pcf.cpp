// pcf.cpp
//
//   Implementation of PcfFuzzTarget.
//
// Copyright 2018 by
// Armin Hasitzka, David Turner, Robert Wilhelm, and Werner Lemberg.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/font-drivers/pcf.h"

#include "iterators/faceloaditerator.h"
#include "iterators/faceprepiterator-bitmaps.h"
#include "visitors/facevisitor-bdf.h"
#include "visitors/facevisitor-charcodes.h"
#include "visitors/facevisitor-variants.h"


  using namespace std;


  PcfFuzzTarget::
  PcfFuzzTarget( void )
  {
    auto  fli          = fuzzing::make_unique<FaceLoadIterator>();
    auto  fpi_bitmaps  = fuzzing::make_unique<FacePrepIteratorBitmaps>();


    // -----------------------------------------------------------------------
    // Face load iterators:

    (void) fli->set_supported_font_format( FaceLoader::FontFormat::PCF );
    
    (void) fli->add_iterator( move( fpi_bitmaps ) );
    
    (void) fli
      ->add_once_visitor(
        fuzzing::make_unique<FaceVisitorBdf>(
          FaceLoader::FontFormat::PCF ) );
    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorCharCodes>() );
    (void) fli
      ->add_once_visitor( fuzzing::make_unique<FaceVisitorVariants>() );

    // -----------------------------------------------------------------------
    // Fuzz target:

    (void) set_iterator( move( fli ) );
  }
