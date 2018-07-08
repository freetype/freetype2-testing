[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
[![Build Status](https://travis-ci.org/cherusker/freetype2-testing.svg?branch=master)](https://travis-ci.org/cherusker/freetype2-testing)

# FreeType

FreeType is a freely available software library to render fonts.

https://www.freetype.org/

# Fuzzing

We run FreeType against test cases that [OSS-Fuzz](https://bugs.chromium.org/p/oss-fuzz/issues/list?can=1&q=proj=freetype2) created to trigger verified bugs that have been fixed officially.

## Fuzzed API Functions

The following tables provide an overview over currently fuzzed and unfuzzed API functions.
Columns have the following meaning:

- **Function**:    The API function name.
- **Used**:        A function is used at least once, by one fuzz target.
- **Extensively**: A function is used in (almost) every way possible and it is up the fuzzer to find inputs that fully test it.
- **Resources**:   Some important resources that a function uses.  This list is by no means complete.  It merely highlights important shared resources that carry over from one function to another.
- **Alias**:       Other functions that do exactly the same.
- **Calls**:       Other API functions that a function calls.  Used to track down implicitely used API functions.
- **Called by**:   Other API functions that call a function.  Used to track down implicitely used API functions.

### FreeType Version

https://www.freetype.org/freetype2/docs/reference/ft2-version.html

|       | Function                       | Used               | Extensively        | Resources |
| ----- | ------------------------------ | :----------------: | :----------------: | --------- |
| 1.1.1 | `FT_Library_Version`           | :heavy_check_mark: | :heavy_check_mark: | Library   |
| 1.1.2 | `FT_Face_CheckTrueTypePatents` | :heavy_check_mark: | :heavy_check_mark: | Face      |
| 1.1.3 | `FT_Face_SetUnpatentedHinting` | :heavy_check_mark: | :heavy_check_mark: | Face      |

### Base Interface

https://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html

|       | Function           | Used               | Extensively        | Resources |
| ----- | ------------------ | :----------------: | :----------------: | --------- |
| 2.1.1 | `FT_Init_FreeType` | :heavy_check_mark: | :heavy_check_mark: |           |
| 2.1.2 | `FT_Done_FreeType` | :heavy_check_mark: | :heavy_check_mark: | Library   |

|       | Function             | Used               | Extensively        | Resources                | Calls | Called by        |
| ----- | -------------------- | :----------------: | :----------------: | ------------------------ | ----- | ---------------- |
| 2.2.1 | `FT_New_Face`        |                    |                    | Library <br> File Path   |       |                  |
| 2.2.2 | `FT_Done_Face`       | :heavy_check_mark: | :heavy_check_mark: | Face                     | 6.1.1 |                  |
| 2.2.3 | `FT_Reference_Face`  |                    |                    | Face                     |       |                  |
| 2.2.4 | `FT_New_Memory_Face` | :heavy_check_mark: | :heavy_check_mark: | Library <br> Bytes       | 2.2.6 |                  |
| 2.2.5 | `FT_Face_Properties` |                    |                    | Face                     |       |                  |
| 2.2.6 | `FT_Open_Face`       | :heavy_check_mark: | :heavy_check_mark: | Library                  | 6.1.2 | 2.2.4 <br> 2.2.8 |
| 2.2.7 | `FT_Attach_File`     |                    |                    | Face <br> File Path      |       |                  |
| 2.2.8 | `FT_Attach_Stream`   | :heavy_check_mark: | :heavy_check_mark: | Face <br> Bytes          | 2.2.6 |                  |

|       | Function             | Used               | Extensively        | Resources | Calls | Called by |
| ----- | -------------------- | :----------------: | :----------------: | --------- | ----- | --------- |
| 2.3.1 | `FT_Set_Char_Size`   | :heavy_check_mark: | :heavy_check_mark: | Face      | 2.3.3 |           |
| 2.3.2 | `FT_Set_Pixel_Sizes` | :heavy_check_mark: | :heavy_check_mark: | Face      |       |           |
| 2.3.3 | `FT_Request_Size`    | :heavy_check_mark: | :heavy_check_mark: | Face      |       | 2.3.1     |
| 2.3.4 | `FT_Select_Size`     | :heavy_check_mark: | :heavy_check_mark: | Face      |       |           |
| 2.3.5 | `FT_Set_Transform`   |                    |                    | Face      |       |           |

|       | Function            | Used               | Extensively        | Resources                             | Calls            | Called by |
| ----- | ------------------- | :----------------: | :----------------: | ------------------------------------- | ---------------- | --------- |
| 2.4.1 | `FT_Load_Glyph`     | :heavy_check_mark: |                    | Face <br> Glyph Index <br> Load Flags |                  | 2.4.6     |
| 2.4.2 | `FT_Get_Char_Index` | :heavy_check_mark: | :heavy_check_mark: | Face <br> Char Code                   |                  | 2.4.6     |
| 2.4.3 | `FT_Get_First_Char` | :heavy_check_mark: | :heavy_check_mark: | Face                                  |                  |           |
| 2.4.4 | `FT_Get_Next_Char`  | :heavy_check_mark: | :heavy_check_mark: | Face <br> Char Code                   |                  |           |
| 2.4.5 | `FT_Get_Name_Index` | :heavy_check_mark: | :heavy_check_mark: | Face                                  |                  |           |
| 2.4.6 | `FT_Load_Char`      |                    |                    | Face <br> Char Code <br> Load Flags   | 2.4.1 <br> 2.4.2 |           |

|       | Function            | Used | Extensively | Resources  |
| ----- | ------------------- | :--: | :---------: | ---------- |
| 2.5.1 | `FT_Render_Glyph`   |      |             | Glyph Slot |

|       | Function               | Used               | Extensively        | Resources                |
| ----- | ---------------------- | :----------------: | :----------------: | ------------------------ |
| 2.6.1 | `FT_Get_Kerning`       | :heavy_check_mark: | :heavy_check_mark: | Face <br> 2x Glyph Index |
| 2.6.2 | `FT_Get_Track_Kerning` |                    |                    | Face                     |

|       | Function                 | Used               | Extensively        | Resources             |
| ----- | ------------------------ | :----------------: | :----------------: | --------------------- |
| 2.7.1 | `FT_Get_Glyph_Name`      | :heavy_check_mark: | :heavy_check_mark: | Face <br> Glyph Index |
| 2.7.2 | `FT_Get_Postscript_Name` | :heavy_check_mark: | :heavy_check_mark: | Face                  |

|       | Function               | Used               | Extensively        | Resources          |
| ----- | ---------------------- | :----------------: | :----------------: | ------------------ |
| 2.8.1 | `FT_Select_Charmap`    | :heavy_check_mark: | :heavy_check_mark: | Face               |
| 2.8.2 | `FT_Set_Charmap`       | :heavy_check_mark: | :heavy_check_mark: | Face <br> Char Map |
| 2.8.3 | `FT_Get_Charmap_Index` | :heavy_check_mark: | :heavy_check_mark: | Face <br> Char Map |

|       | Function               | Used | Extensively | Resources                      |
| ----- | ---------------------- | :--: | :---------: | ------------------------------ |
| 2.9.1 | `FT_Get_FSType_Flags`  |      |             | Face                           |
| 2.9.2 | `FT_Get_SubGlyph_Info` |      |             | Glyph Slot <br> Subglyph Index |

### Unicode Variation Sequences

https://www.freetype.org/freetype2/docs/reference/ft2-glyph_variants.html

|       | Function                          | Used               | Extensively        | Resources                             |
| ----- | --------------------------------- | :----------------: | :----------------: | :-----------------------------------: |
| 3.1.1 | `FT_Face_GetCharVariantIndex`     | :heavy_check_mark: | :heavy_check_mark: | Face <br> Char Code <br> Var Selector |
| 3.1.2 | `FT_Face_GetCharVariantIsDefault` | :heavy_check_mark: | :heavy_check_mark: | Face <br> Char Code <br> Var Selector |
| 3.1.3 | `FT_Face_GetVariantSelectors`     | :heavy_check_mark: | :heavy_check_mark: | Face                                  |
| 3.1.4 | `FT_Face_GetVariantsOfChar`       | :heavy_check_mark: | :heavy_check_mark: | Face <br> Char Code                   |
| 3.1.5 | `FT_Face_GetCharsOfVariant`       | :heavy_check_mark: | :heavy_check_mark: | Face <br> Var Selector                |

### Glyph Management

https://www.freetype.org/freetype2/docs/reference/ft2-glyph_management.html

|       | Function             | Used               | Extensively        | Resources  |
| ----- | -------------------- | :----------------: | :----------------: | ---------- |
| 4.1.1 | `FT_Get_Glyph`       | :heavy_check_mark: | :heavy_check_mark: | Glyph Slot |
| 4.1.2 | `FT_Glyph_Copy`      | :heavy_check_mark: | :heavy_check_mark: | Glyph      |
| 4.1.3 | `FT_Glyph_Transform` | :heavy_check_mark: | :heavy_check_mark: | Glyph      |
| 4.1.4 | `FT_Glyph_Get_CBox`  |                    |                    | Glyph      |
| 4.1.5 | `FT_Glyph_To_Bitmap` |                    |                    | Glyph      |
| 4.1.6 | `FT_Done_Glyph`      | :heavy_check_mark: | :heavy_check_mark: | Glyph      |

### Mac Specific Interface

https://www.freetype.org/freetype2/docs/reference/ft2-mac_specific.html

|       | Function                           | Used | Extensively |
| ----- | ---------------------------------- | :--: | :---------: |
| 5.1.1 | `FT_New_Face_From_FOND`            |      |             |
| 5.1.2 | `FT_GetFile_From_Mac_Name`         |      |             |
| 5.1.3 | `FT_GetFile_From_Mac_ATS_Name`     |      |             |
| 5.1.4 | `FT_GetFilePath_From_Mac_ATS_Name` |      |             |
| 5.1.5 | `FT_New_Face_From_FSSpec`          |      |             |
| 5.1.6 | `FT_New_Face_From_FSRef`           |      |             |

### Size Management

https://www.freetype.org/freetype2/docs/reference/ft2-sizes_management.html

|       | Function           | Used               | Extensively        | Resources | Called by |
| ----- | ------------------ | :----------------: | :----------------: | --------- | --------- |
| 6.1.1 | `FT_New_Size`      | :heavy_check_mark: | :heavy_check_mark: | Face      | 2.2.6     |
| 6.1.2 | `FT_Done_Size`     | :heavy_check_mark: | :heavy_check_mark: | Size      | 2.2.2     |
| 6.1.3 | `FT_Activate_Size` |                    |                    | Size      |           |

### Multiple Masters

https://www.freetype.org/freetype2/docs/reference/ft2-multiple_masters.html

|        | Function                        | Used               | Extensively        | Resources           | Alias  |
| ------ | ------------------------------- | :----------------: | :----------------: | :-----------------: | :----: |
| 7.1.1  | `FT_Get_Multi_Master`           |                    |                    | Face                |        |
| 7.1.2  | `FT_Get_MM_Var`                 | :heavy_check_mark: | :heavy_check_mark: | Face                |        |
| 7.1.3  | `FT_Done_MM_Var`                | :heavy_check_mark: | :heavy_check_mark: | Library <br> MM Var |        |
| 7.1.4  | `FT_Set_MM_Design_Coordinates`  |                    |                    | Face                |        |
| 7.1.5  | `FT_Set_Var_Design_Coordinates` | :heavy_check_mark: | :heavy_check_mark: | Face                |        |
| 7.1.6  | `FT_Get_Var_Design_Coordinates` | :heavy_check_mark: | :heavy_check_mark: | Face                |        |
| 7.1.7  | `FT_Set_MM_Blend_Coordinates`   | :heavy_check_mark: |                    | Face                | 7.1.9  |
| 7.1.8  | `FT_Get_MM_Blend_Coordinates`   | :heavy_check_mark: | :heavy_check_mark: | Face                | 7.1.10 |
| 7.1.9  | `FT_Set_Var_Blend_Coordinates`  | :heavy_check_mark: |                    | Face                | 7.1.7  |
| 7.1.10 | `FT_Get_Var_Blend_Coordinates`  | :heavy_check_mark: | :heavy_check_mark: | Face                | 7.1.8  |
| 7.1.11 | `FT_Get_Var_Axis_Flags`         | :heavy_check_mark: | :heavy_check_mark: | MM Var              |        |
| 7.1.12 | `FT_Set_Named_Instance`         | :heavy_check_mark: |                    | Face                |        |

### TrueType Tables

https://www.freetype.org/freetype2/docs/reference/ft2-truetype_tables.html

|       | Function                  | Used               | Extensively        | Resources |
| ----- | ------------------------- | :----------------: | :----------------: | --------- |
| 8.1.1 | `FT_Get_Sfnt_Table`       | :heavy_check_mark: | :heavy_check_mark: | Face      |
| 8.1.2 | `FT_Load_Sfnt_Table`      | :heavy_check_mark: |                    | Face      |
| 8.1.3 | `FT_Sfnt_Table_Info`      | :heavy_check_mark: | :heavy_check_mark: | Face      |
| 8.1.4 | `FT_Get_CMap_Language_ID` | :heavy_check_mark: | :heavy_check_mark: | Char Map  |
| 8.1.5 | `FT_Get_CMap_Format`      | :heavy_check_mark: | :heavy_check_mark: | Char Map  |

### Type 1 Tables

https://www.freetype.org/freetype2/docs/reference/ft2-type1_tables.html

|       | Function                 | Used | Extensively |
| ----- | ------------------------ | :--: | :---------: |
| 9.1.1 | `FT_Has_PS_Glyph_Names`  |      |             |
| 9.1.2 | `FT_Get_PS_Font_Info`    |      |             |
| 9.1.3 | `FT_Get_PS_Font_Private` |      |             |
| 9.1.4 | `FT_Get_PS_Font_Value`   |      |             |

### SFNT Names

https://www.freetype.org/freetype2/docs/reference/ft2-sfnt_names.html

|        | Function                 | Used | Extensively |
| ------ | ------------------------ | :--: | :---------: |
| 10.1.1 | `FT_Get_Sfnt_Name_Count` |      |             |
| 10.1.2 | `FT_Get_Sfnt_Name`       |      |             |
| 10.1.3 | `FT_SfntLangTag`         |      |             |
| 10.1.4 | `FT_Get_Sfnt_LangTag`    |      |             |

### BDF and PCF Files

https://www.freetype.org/freetype2/docs/reference/ft2-bdf_fonts.html

|        | Function                | Used | Extensively |
| ------ | ----------------------- | :--: | :---------: |
| 11.1.1 | `FT_Get_BDF_Charset_ID` |      |             |
| 11.1.2 | `FT_Get_BDF_Property`   |      |             |

### CID Fonts

https://www.freetype.org/freetype2/docs/reference/ft2-cid_fonts.html

|        | Function                                  | Used               | Extensively        | Resources             |
| ------ | ----------------------------------------- | :----------------: | :----------------: | --------------------- |
| 12.1.1 | `FT_Get_CID_Registry_Ordering_Supplement` | :heavy_check_mark: | :heavy_check_mark: | Face                  |
| 12.1.2 | `FT_Get_CID_Is_Internally_CID_Keyed`      | :heavy_check_mark: | :heavy_check_mark: | Face                  |
| 12.1.3 | `FT_Get_CID_From_Glyph_Index`             | :heavy_check_mark: | :heavy_check_mark: | Face <br> Glyph Index |

### PFR Fonts

https://www.freetype.org/freetype2/docs/reference/ft2-pfr_fonts.html

|        | Function             | Used | Extensively |
| ------ | -------------------- | :--: | :---------: |
| 13.1.1 | `FT_Get_PFR_Metrics` |      |             |
| 13.1.2 | `FT_Get_PFR_Kerning` |      |             |
| 13.1.3 | `FT_Get_PFR_Advance` |      |             |

### Window FNT Files

https://www.freetype.org/freetype2/docs/reference/ft2-winfnt_fonts.html

|        | Function               | Used | Extensively |
| ------ | ---------------------- | :--: | :---------: |
| 14.1.1 | `FT_Get_WinFNT_Header` |      |             |

### Font Formats

https://www.freetype.org/freetype2/docs/reference/ft2-font_formats.html

|        | Function             | Used               | Extensively        | Resources |
| ------ | -------------------- | :----------------: | :----------------: | --------- |
| 15.1.1 | `FT_Get_Font_Format` | :heavy_check_mark: | :heavy_check_mark: | Face      |

### Gasp Table

https://www.freetype.org/freetype2/docs/reference/ft2-gasp_table.html

|        | Function      | Used | Extensively | Resources |
| ------ | ------------- | :--: | :---------: | --------- |
| 16.1.1 | `FT_Get_Gasp` |      |             | Face      |
