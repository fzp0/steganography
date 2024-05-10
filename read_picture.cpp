#include "read_picture.h"

// https://en.wikipedia.org/wiki/BMP_file_format#Bitmap_file_header
void bmp_reader::parse_header(std::ifstream& stream, file_header& header) {
    stream.read(header.header_field, 2);
    fmt::println("Header field: {}", header.header_field);

    stream.read((char*)&header.bmp_size, 4);
    fmt::println("BMP file size: {}", header.bmp_size);

    stream.read(header.reserved, 4);
    fmt::println("Reserved field: {}", header.reserved);

    stream.read((char*)&header.array_offset, 4);
    fmt::println("Picture data array memory address: {}",  header.array_offset);
}

// https://en.wikipedia.org/wiki/BMP_file_format#DIB_header_(bitmap_information_header)
void bmp_reader::parse_dib(std::ifstream &stream, dib_header &dib) {
    stream.read((char*)&dib.dib_size, 4);
    fmt::println("DIB Header size: {}", dib.dib_size);
    switch(dib.dib_size) {
        case 12: // BITMAPCOREHEADER OS21XBITMAPHEADER

            break;
        case 16: // OS22XBITMAPHEADER
        case 64:

            break;
        case 40: // BITMAPINFOHEADER

            break;
        case 52: // BITMAPV2INFOHEADER

            break;
        case 56: // BITMAPV3INFOHEADER

            break;
        case 108: // BITMAPV4HEADER

            break;
        case 124: // BITMAPV5HEADER

            break;
        default:
            fmt::println("Unsupported bitmap file! (DIB size mismatch)");
            exit(0);
    }
}



auto bmp_reader::read_bmp(std::filesystem::path const& file) -> bmp_reader::bmp_data {
    bmp_data ret;
    auto in = std::ifstream(file);
    if(in.good()) {
        parse_header(in, ret.fileheader);
        if(ret.fileheader.header_field == std::string("BM"))
            parse_dib(in, ret.dibheader);
        else {
            fmt::println("Unsupported bitmap file! (header field mismatch)");
            exit(-1);
        }
    }
    in.close();
    return ret;
}