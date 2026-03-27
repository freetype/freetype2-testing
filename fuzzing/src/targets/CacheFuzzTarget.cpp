// CacheFuzzTarget.cpp
//
//   Implementation of CacheFuzzTarget.
//
// Copyright 2024 by
// The FreeType Project.
//
// This file is part of the FreeType project, and may only be used,
// modified, and distributed under the terms of the FreeType project
// license, LICENSE.TXT.  By continuing to use, modify, or distribute
// this file you indicate that you have read the license and
// understand and accept it fully.


#include "targets/CacheFuzzTarget.h"
#include <vector>


  struct RequestData {
    const uint8_t* data;
    size_t size;
  };

  FT_Error
  freetype::CacheFuzzTarget::
  face_requester( FTC_FaceID  face_id,
                  FT_Library  library,
                  FT_Pointer  req_data,
                  FT_Face*    aface )
  {
    RequestData* rdata = (RequestData*)req_data;
    // For simplicity, we always return the same face created from the fuzz data.
    // In a real scenario, face_id could map to different parts of data.
    return FT_New_Memory_Face( library,
                               rdata->data,
                               (FT_Long)rdata->size,
                               0,
                               aface );
  }

  void
  freetype::CacheFuzzTarget::
  run( const uint8_t*  data,
       size_t          size )
  {
    if ( size < 1 )
      return;

    FT_Library  library = get_ft_library();
    FTC_Manager manager;
    FTC_CMapCache cmap_cache;
    FTC_ImageCache image_cache;
    FTC_SBitCache sbit_cache;
    
    RequestData req_data = { data, size };

    // Initialize Cache Manager
    if ( FTC_Manager_New( library, 2, 4, 200000, face_requester, &req_data, &manager ) )
      return;

    if ( FTC_CMapCache_New( manager, &cmap_cache ) ||
         FTC_ImageCache_New( manager, &image_cache ) ||
         FTC_SBitCache_New( manager, &sbit_cache ) )
    {
      FTC_Manager_Done( manager );
      return;
    }

    // Data cursor
    size_t cursor = 0;
    std::vector<FTC_Node> nodes;

    // Helper to get next byte
    auto next_byte = [&]() -> uint8_t {
      if ( cursor >= size ) return 0;
      return data[cursor++];
    };

    // Helper to get next uint16 (for glyph index etc)
    auto next_u16 = [&]() -> uint16_t {
      if ( cursor + 2 > size ) return 0;
      uint16_t v = (uint16_t)data[cursor] | ((uint16_t)data[cursor+1] << 8);
      cursor += 2;
      return v;
    };

    while ( cursor < size )
    {
      uint8_t cmd = next_byte() % 10;
      FTC_FaceID face_id = (FTC_FaceID)(uintptr_t)(1); // Simplified: always use ID 1

      switch ( cmd )
      {
        case 0: // FTC_Manager_Reset
          FTC_Manager_Reset( manager );
          nodes.clear(); // Reset invalidates nodes
          break;

        case 1: // FTC_Manager_LookupFace
        {
          FT_Face face;
          FTC_Manager_LookupFace( manager, face_id, &face );
          break;
        }

        case 2: // FTC_Manager_LookupSize
        {
          FTC_ScalerRec scaler;
          scaler.face_id = face_id;
          scaler.width = next_byte();
          scaler.height = next_byte();
          scaler.pixel = 1;
          scaler.x_res = 72;
          scaler.y_res = 72;
          FT_Size asize;
          FTC_Manager_LookupSize( manager, &scaler, &asize );
          break;
        }

        case 3: // FTC_Manager_RemoveFaceID
          FTC_Manager_RemoveFaceID( manager, face_id );
          nodes.clear(); // Removing face might invalidate nodes
          break;

        case 4: // FTC_ImageCache_Lookup
        {
          FT_UInt gindex = next_u16();
          FT_Glyph glyph;
          FTC_Node node;
          FTC_ImageTypeRec type;
          type.face_id = face_id;
          type.width = next_byte();
          type.height = next_byte();
          type.flags = FT_LOAD_DEFAULT;
          
          if ( !FTC_ImageCache_Lookup( image_cache, &type, gindex, &glyph, &node ) ) {
            if ( node ) nodes.push_back( node );
          }
          break;
        }

        case 5: // FTC_SBitCache_Lookup
        {
          FT_UInt gindex = next_u16();
          FTC_SBit sbit;
          FTC_Node node;
          FTC_ImageTypeRec type;
          type.face_id = face_id;
          type.width = next_byte();
          type.height = next_byte();
          type.flags = FT_LOAD_DEFAULT;

          if ( !FTC_SBitCache_Lookup( sbit_cache, &type, gindex, &sbit, &node ) ) {
            if ( node ) nodes.push_back( node );
          }
          break;
        }

        case 6: // FTC_CMapCache_Lookup
        {
          FT_UInt32 char_code = next_u16();
          FT_Int cmap_index = next_byte() % 4; // Try a few cmap indices
          FTC_CMapCache_Lookup( cmap_cache, face_id, cmap_index, char_code );
          break;
        }
        
        case 7: // FTC_ImageCache_LookupScaler
        {
          FTC_ScalerRec scaler;
          scaler.face_id = face_id;
          scaler.width = next_byte();
          scaler.height = next_byte();
          scaler.pixel = 1;
          scaler.x_res = 72;
          scaler.y_res = 72;
          FT_UInt gindex = next_u16();
          FT_Glyph glyph;
          FTC_Node node;
          
          if ( !FTC_ImageCache_LookupScaler( image_cache, &scaler, FT_LOAD_DEFAULT, gindex, &glyph, &node ) ) {
             if ( node ) nodes.push_back( node );
          }
          break;
        }

        case 8: // FTC_SBitCache_LookupScaler
        {
          FTC_ScalerRec scaler;
          scaler.face_id = face_id;
          scaler.width = next_byte();
          scaler.height = next_byte();
          scaler.pixel = 1;
          scaler.x_res = 72;
          scaler.y_res = 72;
          FT_UInt gindex = next_u16();
          FTC_SBit sbit;
          FTC_Node node;

          if ( !FTC_SBitCache_LookupScaler( sbit_cache, &scaler, FT_LOAD_DEFAULT, gindex, &sbit, &node ) ) {
            if ( node ) nodes.push_back( node );
          }
          break;
        }

        case 9: // Random unref
        {
          if ( !nodes.empty() ) {
            size_t idx = next_byte() % nodes.size();
            FTC_Node_Unref( nodes[idx], manager );
            nodes.erase( nodes.begin() + idx );
          }
          break;
        }
      }
    }

    // Cleanup remaining nodes
    for ( FTC_Node node : nodes ) {
      FTC_Node_Unref( node, manager );
    }

    FTC_Manager_Done( manager );
  }
