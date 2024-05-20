#pragma once

struct BITMAPCOREHEADER {
    uint32_t header_size;
    uint16_t width;
    uint16_t height;
    uint16_t num_color_planes; // wikipedia says must be 1
    uint16_t bits_per_pixel;
};


enum COMPRESSION_METHOD {
    BI_RGB = 0,
    BI_RLE8 = 1,
    BI_RLE4 = 2,
    BI_BITFIELDS = 3,
    BI_JPEG = 4,
    BI_PNG = 5,
    BI_ALPHABITFIELDS = 6,
    BI_CMYK = 11,
    BI_CMYKRLE8 = 12,
    BI_CMYKRLE4 = 13
};


struct BITMAPINFOHEADER {
    uint32_t header_size;
    int width;
    int height;
    uint16_t num_color_planes; // wikipedia says must be 1
    uint16_t bits_per_pixel;
    uint32_t compression_method;
    uint32_t raw_bitmap_data_size;
    int horizontal_resolution;
    int vertical_resolution;
    uint32_t num_palette_colors; // 0 = 2^n colors
    uint32_t num_important_colors; // 0 = every color is important
};

struct OS22XBITMAPHEADER {
    BITMAPINFOHEADER info_header;
    uint16_t enum_resolution_unit; // 0 = pixels per meter
    uint16_t pad0;
    uint16_t enum_bit_fill_direction; // 0 = The origin is the lower-left corner. Bits fill from left-to-right, then bottom-to-top.
    uint16_t enum_halftoning_algorithm;
    uint32_t halftoning_param1;
    uint32_t halftoning_param2;
    uint32_t enum_color_encoding; // 0 = RGB
    uint32_t application_identifier;
};



