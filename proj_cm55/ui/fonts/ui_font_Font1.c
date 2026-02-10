/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font C:/Users/bhatt/Downloads/Hackathon_squareline/assets/SourceSans3-SemiBold.ttf -o C:/Users/bhatt/Downloads/Hackathon_squareline/assets\ui_font_Font1.c --format lvgl -r 0x20-0x7f --symbols ° --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_FONT1
#define UI_FONT_FONT1 1
#endif

#if UI_FONT_FONT1

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0x30,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x24, 0x4b, 0xfb, 0x66, 0xc9, 0xbf, 0xa4, 0x48,
    0x90,

    /* U+0024 "$" */
    0x30, 0xc7, 0xbf, 0xc3, 0x7, 0xe, 0x1c, 0x38,
    0xfe, 0x30, 0xc0,

    /* U+0025 "%" */
    0x70, 0x86, 0xc4, 0x36, 0x41, 0xb7, 0xed, 0xb9,
    0xba, 0xcc, 0x16, 0x61, 0x33, 0x11, 0x98, 0x87,
    0x80,

    /* U+0026 "&" */
    0x3c, 0x19, 0x86, 0x61, 0xb0, 0x38, 0x1e, 0x3d,
    0xcb, 0x1e, 0xc3, 0x9f, 0x30,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x22, 0x66, 0xcc, 0xcc, 0xcc, 0xc6, 0x62, 0x20,

    /* U+0029 ")" */
    0x44, 0x66, 0x33, 0x33, 0x33, 0x36, 0x64, 0x40,

    /* U+002A "*" */
    0x25, 0x7e, 0xe5, 0x0,

    /* U+002B "+" */
    0x18, 0x30, 0x67, 0xf1, 0x83, 0x6, 0x0,

    /* U+002C "," */
    0xf3, 0x64,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x8, 0x46, 0x21, 0x18, 0x84, 0x23, 0x10, 0x84,
    0x60,

    /* U+0030 "0" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x6c,
    0x70,

    /* U+0031 "1" */
    0x33, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x33, 0xf0,

    /* U+0032 "2" */
    0x79, 0x18, 0x30, 0x60, 0xc3, 0xe, 0x38, 0x61,
    0xfc,

    /* U+0033 "3" */
    0x7c, 0x8c, 0x18, 0x73, 0x81, 0xc1, 0x83, 0x46,
    0xf8,

    /* U+0034 "4" */
    0xe, 0xe, 0x1e, 0x36, 0x26, 0x66, 0xff, 0x6,
    0x6, 0x6,

    /* U+0035 "5" */
    0x7e, 0xc1, 0x83, 0x7, 0xc1, 0xc1, 0x83, 0xce,
    0xf0,

    /* U+0036 "6" */
    0x3c, 0xcb, 0x6, 0xd, 0xdc, 0xf1, 0xe3, 0x66,
    0x78,

    /* U+0037 "7" */
    0xfe, 0x8, 0x30, 0xc1, 0x82, 0xc, 0x18, 0x30,
    0x60,

    /* U+0038 "8" */
    0x7d, 0x8f, 0x1f, 0x37, 0xcf, 0xb1, 0xe3, 0xc6,
    0xf8,

    /* U+0039 "9" */
    0x79, 0x9b, 0x1e, 0x3c, 0xee, 0xc1, 0x83, 0x4c,
    0xf0,

    /* U+003A ":" */
    0xc0, 0x3,

    /* U+003B ";" */
    0xc0, 0x0, 0x7, 0x7e, 0x0,

    /* U+003C "<" */
    0x2, 0x1d, 0xe6, 0xf, 0x3, 0xc1, 0x80,

    /* U+003D "=" */
    0xfe, 0x0, 0x7, 0xf0,

    /* U+003E ">" */
    0x81, 0xc0, 0xf0, 0x31, 0xfe, 0x30, 0x0,

    /* U+003F "?" */
    0x79, 0x30, 0xc3, 0x18, 0x63, 0xc, 0x0, 0xc0,

    /* U+0040 "@" */
    0x7, 0xc0, 0xc3, 0x8c, 0xc, 0xcf, 0x3c, 0xd9,
    0xec, 0xcf, 0x64, 0x7b, 0x26, 0xce, 0xe6, 0x0,
    0x18, 0x0, 0x61, 0x1, 0xf8, 0x0,

    /* U+0041 "A" */
    0x1c, 0xa, 0x5, 0x6, 0xc3, 0x61, 0x19, 0xfc,
    0xc6, 0xc1, 0xe0, 0xc0,

    /* U+0042 "B" */
    0xfc, 0xc6, 0xc6, 0xc6, 0xfc, 0xc7, 0xc3, 0xc3,
    0xc7, 0xfc,

    /* U+0043 "C" */
    0x1e, 0x62, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0,
    0x63, 0x3e,

    /* U+0044 "D" */
    0xf8, 0xc6, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7,
    0xc6, 0xfc,

    /* U+0045 "E" */
    0xff, 0x83, 0x6, 0xf, 0xd8, 0x30, 0x60, 0xc1,
    0xfc,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xf, 0xd8, 0x30, 0x60, 0xc1,
    0x80,

    /* U+0047 "G" */
    0x1e, 0x62, 0x40, 0xc0, 0xcf, 0xc3, 0xc3, 0xc3,
    0x63, 0x3e,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xf0,

    /* U+004A "J" */
    0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0x8f, 0xe0,

    /* U+004B "K" */
    0xc6, 0xc6, 0xcc, 0xd8, 0xf8, 0xec, 0xec, 0xc6,
    0xc6, 0xc3,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xf0,

    /* U+004D "M" */
    0xe3, 0xf1, 0xf8, 0xfe, 0xff, 0x7e, 0xaf, 0x57,
    0xbb, 0xc9, 0xe0, 0xc0,

    /* U+004E "N" */
    0xe3, 0xe3, 0xf3, 0xf3, 0xdb, 0xdb, 0xcf, 0xcf,
    0xc7, 0xc7,

    /* U+004F "O" */
    0x3e, 0x31, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xc2, 0x63, 0x1f, 0x0,

    /* U+0050 "P" */
    0xfd, 0x8f, 0x1e, 0x3c, 0xff, 0xb0, 0x60, 0xc1,
    0x80,

    /* U+0051 "Q" */
    0x3e, 0x31, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x82, 0x63, 0x1f, 0x3, 0x0, 0xc0, 0x38,

    /* U+0052 "R" */
    0xfd, 0x8f, 0x1e, 0x3c, 0xff, 0xb6, 0x66, 0xcd,
    0x8c,

    /* U+0053 "S" */
    0x7d, 0x8b, 0x7, 0x7, 0xc7, 0xc3, 0x83, 0x87,
    0xf0,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x66, 0x3c,

    /* U+0056 "V" */
    0xc1, 0x61, 0x98, 0xcc, 0x46, 0x61, 0x30, 0xd0,
    0x68, 0x1c, 0xe, 0x0,

    /* U+0057 "W" */
    0xc6, 0x13, 0x39, 0x99, 0xcc, 0xca, 0x66, 0xd3,
    0x36, 0xd0, 0xb7, 0x87, 0x3c, 0x38, 0xe1, 0xc7,
    0x0,

    /* U+0058 "X" */
    0x63, 0x62, 0x36, 0x34, 0x1c, 0x1c, 0x3c, 0x36,
    0x63, 0xc3,

    /* U+0059 "Y" */
    0xc3, 0x62, 0x66, 0x24, 0x3c, 0x18, 0x18, 0x18,
    0x18, 0x18,

    /* U+005A "Z" */
    0xfe, 0x1c, 0x30, 0xc1, 0x86, 0x8, 0x30, 0xc1,
    0xfc,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,

    /* U+005C "\\" */
    0xc2, 0x10, 0xc2, 0x10, 0x86, 0x10, 0x84, 0x30,
    0x84,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,

    /* U+005E "^" */
    0x30, 0xc7, 0x92, 0xcf, 0x10,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0xc6, 0x20,

    /* U+0061 "a" */
    0x7c, 0x8c, 0x1b, 0xfe, 0x78, 0xf3, 0xbf,

    /* U+0062 "b" */
    0xc1, 0x83, 0x7, 0xec, 0xd8, 0xf1, 0xe3, 0xc7,
    0x9b, 0xe0,

    /* U+0063 "c" */
    0x3d, 0x9c, 0x30, 0xc3, 0x6, 0x4f,

    /* U+0064 "d" */
    0x6, 0xc, 0x19, 0xf6, 0x78, 0xf1, 0xe3, 0xc6,
    0xcd, 0xf8,

    /* U+0065 "e" */
    0x3c, 0xcf, 0x1f, 0xfc, 0x18, 0x18, 0x1f,

    /* U+0066 "f" */
    0x3b, 0x19, 0xf6, 0x31, 0x8c, 0x63, 0x18,

    /* U+0067 "g" */
    0x7f, 0x8b, 0x1e, 0x33, 0xd8, 0x30, 0x3e, 0xc7,
    0x8d, 0xf0,

    /* U+0068 "h" */
    0xc1, 0x83, 0x7, 0xee, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+0069 "i" */
    0xc3, 0xff, 0xfc,

    /* U+006A "j" */
    0x30, 0x3, 0x33, 0x33, 0x33, 0x33, 0x3e,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x3c, 0xdb, 0x3c, 0x7c, 0xcd,
    0x9b, 0x18,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb6, 0xdb, 0x80,

    /* U+006D "m" */
    0xfd, 0xee, 0x73, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63,

    /* U+006E "n" */
    0xfd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+0070 "p" */
    0xfd, 0x9b, 0x1e, 0x3c, 0x78, 0xf3, 0x7c, 0xc1,
    0x83, 0x0,

    /* U+0071 "q" */
    0x3e, 0xcf, 0x1e, 0x3c, 0x78, 0xd9, 0xbf, 0x6,
    0xc, 0x18,

    /* U+0072 "r" */
    0xff, 0x31, 0x8c, 0x63, 0x18,

    /* U+0073 "s" */
    0x7b, 0xc, 0x3e, 0x3c, 0x38, 0xfe,

    /* U+0074 "t" */
    0x63, 0x3e, 0xc6, 0x31, 0x8c, 0x61, 0xc0,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf3, 0xbf,

    /* U+0076 "v" */
    0xc3, 0x66, 0x66, 0x66, 0x24, 0x3c, 0x3c, 0x18,

    /* U+0077 "w" */
    0x46, 0x26, 0x66, 0x6f, 0x66, 0xf6, 0x2b, 0x42,
    0x94, 0x39, 0xc3, 0x9c,

    /* U+0078 "x" */
    0x66, 0xc8, 0xf0, 0xc3, 0x85, 0x99, 0xa3,

    /* U+0079 "y" */
    0xc3, 0x62, 0x66, 0x26, 0x34, 0x3c, 0x18, 0x18,
    0x18, 0x10, 0x60,

    /* U+007A "z" */
    0xfc, 0x61, 0x8c, 0x31, 0x8c, 0x3f,

    /* U+007B "{" */
    0x76, 0x66, 0x66, 0xc6, 0x66, 0x66, 0x63,

    /* U+007C "|" */
    0xff, 0xff,

    /* U+007D "}" */
    0xc6, 0x66, 0x66, 0x36, 0x66, 0x66, 0x6c,

    /* U+007E "~" */
    0xe5, 0x38,

    /* U+00B0 "°" */
    0x69, 0x96
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 51, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 81, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 123, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 131, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 27, .adv_w = 215, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 164, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 70, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 58, .adv_w = 83, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 66, .adv_w = 83, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 74, .adv_w = 112, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 78, .adv_w = 131, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 85, .adv_w = 70, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 87, .adv_w = 82, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 88, .adv_w = 70, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 88, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 98, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 131, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 70, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 70, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 195, .adv_w = 131, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 202, .adv_w = 131, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 206, .adv_w = 131, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 213, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 243, .adv_w = 143, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 153, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 265, .adv_w = 147, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 138, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 161, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 170, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 72, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 153, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 129, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 191, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 168, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 149, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 410, .adv_w = 152, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 140, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 168, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 137, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 205, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 138, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 83, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 513, .adv_w = 88, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 522, .adv_w = 83, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 529, .adv_w = 131, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 534, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 535, .adv_w = 141, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 537, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 144, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 118, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 144, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 81, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 594, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 67, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 67, .box_w = 4, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 614, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 69, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 629, .adv_w = 216, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 143, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 141, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 144, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 666, .adv_w = 144, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 676, .adv_w = 95, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 92, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 694, .adv_w = 142, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 127, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 191, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 123, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 728, .adv_w = 127, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 739, .adv_w = 113, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 83, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 752, .adv_w = 65, .box_w = 1, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 754, .adv_w = 83, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 761, .adv_w = 131, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 763, .adv_w = 89, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 1, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_Font1 = {
#else
lv_font_t ui_font_Font1 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_FONT1*/

