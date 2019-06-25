// type1-ftengine.h
//
//   Fuzz Type 1 faces using FreeType's hinting engine.
//
// Copyright 2019 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef TARGETS_FONT_DRIVERS_TYPE_1_FT_ENGINE_H_
#define TARGETS_FONT_DRIVERS_TYPE_1_FT_ENGINE_H_


#include "targets/font-drivers/type1.h"


  class Type1FtEngineFuzzTarget
    : public Type1FuzzTarget
  {
  public:


    Type1FtEngineFuzzTarget( void );
  };


#endif // TARGETS_FONT_DRIVERS_TYPE_1_FT_ENGINE_H_
