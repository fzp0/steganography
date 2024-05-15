#include "read_picture.h"

// https://en.wikipedia.org/wiki/BMP_file_format#Bitmap_file_header
void bmp_reader::parse_header(std::ifstream& stream, bmp_data& data) {
    auto& header = data.fileheader;
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
void bmp_reader::parse_dib(std::ifstream &stream, bmp_data &data) {
    auto& dib = data.dibheader;
    stream.read((char*)&dib.dib_size, 4);
    fmt::println("DIB Header size: {}", dib.dib_size);
    stream.seekg(stream.tellg() - std::streampos(4));


    std::string data_between_header_and_pixels;
    switch(dib.dib_size) {
        case 12: // BITMAPCOREHEADER OS21XBITMAPHEADER

            break;
        case 16: // OS22XBITMAPHEADER
        case 64:

            break;
        case 40: // BITMAPINFOHEADER
            fmt::println("Bitmap header type: BITMAPINFOHEADER");
            BITMAPINFOHEADER header;
            stream.read((char*)&header, 40);
            fmt::println("Bitmap Width: {}\nBitmap Height: {}", header.width, header.height);
            fmt::println("Color planes: {}", header.num_color_planes);
            fmt::println("Bytes per pixel: {}", header.bytes_per_pixel);
            fmt::println("Compression method: {}", header.compression_method);
            fmt::println("Bitmap data size: {}", header.raw_bitmap_data_size);
            fmt::println("Horizontal resolution: {}", header.horizontal_resolution);
            fmt::println("Vertical resolution: {}", header.vertical_resolution);
            fmt::println("Color pallette: {}", header.num_palette_colors);
            fmt::println("Important colors: {}", header.num_important_colors);

            // Current offset from file start ->52 = 12 (bmp header) + 40 (DIB BITMAPINFOHEADER)
            fmt::println("stream pos: {}", static_cast<int>(stream.tellg()));
            if(header.compression_method != 0){
                fmt::println("Unsupported bitmap compression method: {}", header.compression_method);
                exit(-1);
            }

            int num_colors = header.bytes_per_pixel == 8 ? 256 : pow(header.bytes_per_pixel,2);

            if(header.bytes_per_pixel <= 8){ // ColorTable
                color_table colortable[num_colors];
                for(int i = 0; i < num_colors; i++){
                    stream.read((char*)&colortable[i], 4);

                    fmt::println("Colortable[{}] Red: {} Green: {} Blue: {}", i, colortable[i].red, colortable[i].green, colortable[i].blue);
                }
            }else{


            }

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
        parse_header(in, ret);
        if(ret.fileheader.header_field == std::string("BM"))
            parse_dib(in, ret);
        else {
            fmt::println("Unsupported bitmap file! (header field mismatch)");
            exit(-1);
        }
    }
    in.close();
    return ret;
}