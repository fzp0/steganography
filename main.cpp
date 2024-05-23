#include <iostream>
#include <filesystem>
#include <chrono>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <SFML/Graphics/Image.hpp>
#include "read_picture.h"



void display_image_info(sf::Image& image) {
    auto sizevec = image.getSize();
    fmt::println("Image Width: {}, Image Height: {}", sizevec.x, sizevec.y);
}


void handle_file_extension(std::filesystem::path const& file) {
    fmt::println("Name: {}", file.filename().string());
    fmt::println("Size: {} bytes",file_size(file));
    auto p = std::chrono::file_clock::to_sys(
            std::filesystem::last_write_time(file)
            );
    fmt::println("Last Modified Timestamp: {:%Y-%m-%d %H:%M:%S}", p);
    std::string extension = file.extension().string();
    auto image = sf::Image();
    if(!image.loadFromFile(file.string())){
        fmt::println("invalid file - loadFromFile() failed");
        exit(-1);
    }

    //no switch case for string :c
    if(extension == ".bmp"){
        fmt::println("Extension: .bmp - The BMP file format or bitmap,\nis a raster graphics image file format used to store bitmap digital images, independently of the display device\n(such as a graphics adapter), especially on Microsoft Windows[2] and OS/2[3] operating systems.");
        display_image_info(image);
    }
    else if(extension == ".png") {
        fmt::println("Extension: .png - Portable Network Graphics (PNG) is a raster-graphics file format that supports lossless data compression.");
        display_image_info(image);
    }
    else if(extension == ".tga"){
        fmt::println("Extension: .tga - Truevision TGA, often referred to as TARGA, is a raster graphics file format created by Truevision Inc. (now part of Avid Technology). It was the native format of TARGA and VISTA boards, which were the first graphic cards for IBM-compatible PCs to support Highcolor/truecolor display. This family of graphic cards was intended for professional computer image synthesis and video editing with PCs; for this reason, usual resolutions of TGA image files match those of the NTSC and PAL video formats.");
        display_image_info(image);
    }
    else if(extension == ".jpg" || extension == ".jpeg"){
        fmt::println("Extension: .jpg/.jpeg - JPEG (short for Joint Photographic Experts Group) is a commonly used method of lossy compression for digital images, particularly for those images produced by digital photography.");
        display_image_info(image);
    }
    else if(extension == ".gif"){
        fmt::println("Extension: .gif - The Graphics Interchange Format (GIF) is a bitmap image format that was developed by a team at the online services provider CompuServe led by American computer scientist Steve Wilhite and released on June 15, 1987.");
        display_image_info(image);
    }
    else if(extension == ".psd"){
        fmt::println("Extension: .psd - PSD files are the native file format of Adobe Photoshop.");
        display_image_info(image);
    }
    else if(extension == ".hdr"){
        fmt::println("Extension: .hdr - The original Radiance picture format (typically .pic) is the basis for one of the standard HDR (High Dynamic Range image) image formats (.hdr), supported by most HDR image editors including Adobe PhotoShop (eg: PhotoShop CS2, 2006). Each pixel is stored as 4 bytes, one byte mantissa for each r,g,b and a shared one byte exponent. The pixel data may be stored uncompressed or using a straightforward run length encoding scheme.");
        display_image_info(image);
    }
    else if(extension == ".pic"){
        fmt::println("Extension: .pic - PICtor is an image file format developed by John Bridges, the principal author of PCPaint, the first Paintbrush program for the PC. It was also the native file format for Pictor Paint and Graphics Animation System for Professionals (GRASP) (also by Bridges) and became the first widely accepted DOS imaging standard.");
        display_image_info(image);
    }
    else if(extension == ".ppm"){

    }
    else if(extension == ".pgm"){

    }
    else{
        fmt::println("Unsupported File Extension: {}", file.extension().string());
    }

}


void print_help(){
    fmt::println("--- Steganography ---");
    fmt::println("Program for hiding a string of text inside an image.");
    fmt::println("Supported image types: .bmp .ppm");
    fmt::println("-- Program flags --");
    fmt::println("Syntax: flag [alias] (argument1) (argument2) ... : description");
    fmt::println("-h [-help] : Displays this menu");
    fmt::println("-i [-info] (path) : Displays info about the specified file");
    fmt::println("-e [-encrypt] (path) (message) : Encrypts a message in the specified file");
    fmt::println("-d [-decrypt] (path) : Decrypts a message from the specified file");
    fmt::println("-c [-check] (path) : Checks if a message can be encrypted or hidden inside the specified file");
}

int main(int argc, char** argv) {
    // handle arguments
    if(argc <= 1) {
        print_help();
        exit(-1);
    }

    const std::string flag = argv[1];

    if(flag == "-h" || flag == "-help") {
        if(argc != 2){
            fmt::println("Invalid argument count.");
            return -1;
        }
        print_help();
    }
    else if(flag == "-i" || flag == "-info") {
        if(argc != 3){
            fmt::println("Invalid argument count.");
            return -1;
        }
        auto path = std::filesystem::path(argv[2]);
        if(!std::filesystem::exists(path)) {
            fmt::println("File at the specified path doesn't exist");
            return 0;
        }
        else {
            handle_file_extension(path);
        }

    }
    else if(flag == "-c" || flag == "-check"){
        if(!argc != 4){
            fmt::println("Invalid argument count.");
            return -1;
        }
    }

    return 0;
}
