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

    struct dib_header {
        uint32_t dib_size;
    };

    struct pixel_array {

    };

    struct bmp_data {
        file_header fileheader;
        dib_header dibheader;
        pixel_array pixelarray;
    };

    void parse_header(std::ifstream& stream, file_header& header);
    void parse_dib(std::ifstream& stream, dib_header& dib);


    auto parse_bitmapinfoheader(std::ifstream& stream) -> BITMAPINFOHEADER;

    auto read_bmp(std::filesystem::path const& file) -> bmp_data;
}

