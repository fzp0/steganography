#include <iostream>
#include <fmt/core.h>
#include <filesystem>
#include "read_picture.h"



void display_file_info(std::filesystem::path const& file) {
    fmt::println("Name: {}", file.filename().string());
    fmt::println("Size: {} bytes",file_size(file));
    std::string extension = file.extension().string();
    if(extension == ".bmp"){
        fmt::println("Extension: {} - The BMP file format or bitmap,\nis a raster graphics image file format used to store bitmap digital images, independently of the display device\n(such as a graphics adapter), especially on Microsoft Windows[2] and OS/2[3] operating systems.", file.extension().string());
        auto bmp_info = bmp_reader::read_bmp(file, true);
    }
    else if(extension == ".ppm"){

    }
    else{
        fmt::println("Extension: {} - Unsupported File Extension", file.extension().string());
    }

}




int main(int argc, char** argv) {
    // handle arguments
    if(argc <= 1) {
        fmt::println("Insufficient arguments, execute program with -h flag to see the help menu");
        exit(-1);
    }


    const std::string flag = argv[1];

    if(flag == "-h" || flag == "-help") {

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
    else if(flag == "-i" || flag == "-info") {

        auto path = std::filesystem::path(argv[2]);
        if(!std::filesystem::exists(path)) {
            fmt::println("File at the specified path doesn't exist");
            return 0;
        }
        else {
            display_file_info(path);
            fmt::println("done!");
        }

    }




    return 0;
}
