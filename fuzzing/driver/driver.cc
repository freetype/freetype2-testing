// driver.cc
//
//   Entry point for the test driver.
//
// Copyright 2018 by
// Armin Hasitzka.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>


  // The legacy version is a monolith but it is the only
  // target that calls LLVMFuzzerTestOneInput(...) directly
  // which is why we get away with using it to invoke the
  // legacy target.
  extern "C" int
  LLVMFuzzerTestOneInput( const uint8_t*  data,
                          size_t          size );


  int
  print_error ( std::string const&  message )
  {
    std::cerr << message << "\n";
    return EXIT_FAILURE;
  }


  int
  print_usage ( void )
  {
    return print_error( "\nUsage: driver TYPE FILE\n\n" \
                        "Type:\n" \
                        "  --legacy\n\n" \
                        "File: location of an input file\n" );
  }


  int
  main( int     argc,
        char**  argv )
  {

    if ( argc != 3 )
    {
      return print_usage();
    }
    
    std::string input_file_arg( argv[2] );

    std::ifstream input_file( input_file_arg, std::ios_base::binary );
    if (!input_file)
    {
      return print_error( "error: invalid file: " + input_file_arg );
    }

    std::vector<char> input( ( std::istreambuf_iterator<char>(input_file) ),
                             std::istreambuf_iterator<char>() );

    uint8_t* data = reinterpret_cast<uint8_t*>( &input[0] );
    size_t size = input.size();

    std::string type_arg( argv[1] );

    if ( type_arg.compare( "--legacy" ) == 0 )
    {
      ( void ) LLVMFuzzerTestOneInput( data, size );
    }
    else
    {
      return print_usage();
    }

    return EXIT_SUCCESS;
  }
