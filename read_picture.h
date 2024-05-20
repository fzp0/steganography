#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include "fmt/format.h"
#include "dib_headers.h"


namespace bmp_reader {
    struct file_header {
        char header_field[2];
        uint32_t bmp_size;
        char reserved[4];
        uintptr_t array_offset;
    };

    struct dib_header { // shared data in every bitmap header
        uint32_t dib_size;
        int width;
        int height;
        int num_color_planes;
        int bits_per_pixel;
    };


    struct color_table{
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t pad;
    };


    struct bmp_data {
        file_header fileheader;
        dib_header dibheader;
        std::vector<color_table> colortable;
        void* pixelarray;
    };

    void parse_header(std::ifstream& stream, bmp_data& data, bool print);
    void parse_dib(std::ifstream& stream, bmp_data& data, bool print);

    auto parse_bitmapcoreheader(std::ifstream& stream, bmp_data& data, bool print) -> BITMAPCOREHEADER;
    auto parse_bitmapinfoheader(std::ifstream& stream, bmp_data& data, bool print) -> BITMAPINFOHEADER;
    auto parse_os22xbitmapheader(std::ifstream& stream, bmp_data& data, bool print) -> OS22XBITMAPHEADER;

    auto read_bmp(std::filesystem::path const& file, bool print) -> bmp_data;
}

