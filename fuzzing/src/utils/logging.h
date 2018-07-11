// logging.h
//
//   Switch between different loggers and/or compile them out completely.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#ifndef UTILS_LOGGING_H_
#define UTILS_LOGGING_H_


#ifdef LOGGER_GLOG

#include <glog/logging.h>

#else // LOGGER_GLOG

#include <iostream>

// Note: the semicolon is important to preserve statements like:
// `if ( foo ) LOG( INFO ) << "Hello world!";'

#define LOG( a )       ; if ( 0 ) std::cout
#define LOG_IF( a, b ) ; if ( 0 ) std::cout

#endif // LOGGER_GLOG


#endif // UTILS_LOGGING_H_
