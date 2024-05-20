#include "read_picture.h"

auto bmp_reader::parse_bitmapcoreheader(std::ifstream &stream, bmp_reader::bmp_data &data, bool print) -> BITMAPCOREHEADER {
    BITMAPCOREHEADER header;
    stream.read((char*)&header, 12);
    if(print){
        fmt::println("Bitmap Width: {}\nBitmap Height: {}", header.width, header.height);
        fmt::println("Color planes: {}", header.num_color_planes);
        fmt::println("Bits per pixel: {}", header.bits_per_pixel);
    }

    data.dibheader.width = header.width;
    data.dibheader.height = header.height;
    data.dibheader.num_color_planes = header.num_color_planes;
    data.dibheader.bits_per_pixel = header.bits_per_pixel;

    return header;
}

auto bmp_reader::parse_bitmapinfoheader(std::ifstream &stream, bmp_data& data, bool print) -> BITMAPINFOHEADER {
    BITMAPINFOHEADER header;
    stream.read((char*)&header, 40);
    if(print) {
        fmt::println("Bitmap Width: {}\nBitmap Height: {}", header.width, header.height);
        fmt::println("Color planes: {}", header.num_color_planes);
        fmt::println("Bits per pixel: {}", header.bits_per_pixel);
        fmt::println("Compression method: {}", header.compression_method);
        fmt::println("Bitmap data size: {}", header.raw_bitmap_data_size);
        fmt::println("Horizontal resolution: {}", header.horizontal_resolution);
        fmt::println("Vertical resolution: {}", header.vertical_resolution);
        fmt::println("Color pallette: {}", header.num_palette_colors);
        fmt::println("Important colors: {}", header.num_important_colors);

        // Current offset from file start ->52 = 12 (bmp header) + 40 (DIB BITMAPINFOHEADER)
        //fmt::println("stream pos: {}", static_cast<int>(stream.tellg()));
    }
    if(header.compression_method != 0){
        fmt::println("Unsupported bitmap compression method: {}", header.compression_method);
        exit(-1);
    }

    int num_colors = header.bits_per_pixel == 8 ? 256 : pow(header.bits_per_pixel,2);

    if(header.bits_per_pixel <= 8){ // ColorTable
        for(int i = 0; i < num_colors; i++){
            color_table table;
            stream.read((char*)&table, 4);
            data.colortable.push_back(table);
            if(print)fmt::println("Colortable[{}] Red: {} Green: {} Blue: {}", i, table.red, table.green, table.blue);
        }

        return header;
    }else{
        return header;
    }
}


// https://en.wikipedia.org/wiki/BMP_file_format#DIB_header_(bitmap_information_header)
void bmp_reader::parse_dib(std::ifstream &stream, bmp_data &data, bool print) {
    auto& dib = data.dibheader;
    stream.read((char*)&dib.dib_size, 4);
    if(print)fmt::println("DIB Header size: {}", dib.dib_size);
    stream.seekg(stream.tellg() - std::streampos(4));

    std::string data_between_header_and_pixels;

    // no switch because initializing variables :(
    if(dib.dib_size == 12){ // BITMAPCOREHEADER OS21XBITMAPHEADER

    }else if(dib.dib_size == 16 || dib.dib_size == 64){ // OS22XBITMAPHEADER

    }else if(dib.dib_size == 40){ // BITMAPINFOHEADER
        if(print)fmt::println("DIB Header: BITMAPINFOHEADER (size 40)");
        auto header = parse_bitmapinfoheader(stream,data, print);
    }else if(dib.dib_size == 52){ // BITMAPV2INFOHEADER

    }else if(dib.dib_size == 56){ // BITMAPV3INFOHEADER

    }else if(dib.dib_size == 108){ // BITMAPV4HEADER

    }else if(dib.dib_size == 124){ // BITMAPV5HEADER

    }else{
        fmt::println("DIB Header size mismatch: {}", dib.dib_size);
        exit(-1);
    }
}

// https://en.wikipedia.org/wiki/BMP_file_format#Bitmap_file_header
void bmp_reader::parse_header(std::ifstream& stream, bmp_data& data, bool print) {
    auto& header = data.fileheader;
    stream.read(header.header_field, 2);
    if(print)fmt::println("Header field: {}", header.header_field);

    stream.read((char*)&header.bmp_size, 4);
    if(print)fmt::println("BMP file size: {}", header.bmp_size);

    stream.read(header.reserved, 4);
    if(print)fmt::println("Reserved field: {}", header.reserved);

    stream.read((char*)&header.array_offset, 4);
    if(print)fmt::println("Picture data array offset: {}",  header.array_offset);
}



auto bmp_reader::read_bmp(std::filesystem::path const& file, bool print) -> bmp_reader::bmp_data {
    bmp_data ret;
    auto in = std::ifstream(file);
    if(in.good()) {
        parse_header(in, ret, print);
        if(ret.fileheader.header_field == std::string("BM"))
            parse_dib(in, ret, print);
        else {
            fmt::println("Unsupported bitmap file! (header field mismatch)");
            exit(-1);
        }
    }
    in.close();
    return ret;
}