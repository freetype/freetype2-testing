// bdf.h
//
//   Fuzz BDF faces.
//
// Copyright 2019 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_BDF_H_
#define TARGETS_FONT_DRIVERS_BDF_H_


#include "targets/FaceFuzzTarget.h"


  class BdfFuzzTarget
    : public FaceFuzzTarget
  {
  public:


    BdfFuzzTarget( void );
  };


#endif // TARGETS_FONT_DRIVERS_BDF_H_
