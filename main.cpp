#include <iostream>
#include <fmt/core.h>
#include <filesystem>
#include <chrono>
#include "read_picture.h"
#include <SFML/Graphics/Image.hpp>


void display_image_info(sf::Image& image){
    auto sizevec = image.getSize();
    fmt::println("BMP Width: {}, BMP Height: {}", sizevec.x, sizevec.y);
}


void handle_file_extension(std::filesystem::path const& file) {
    fmt::println("Name: {}", file.filename().string());
    fmt::println("Size: {} bytes",file_size(file));
    auto p = std::filesystem::last_write_time(file);
    auto c = file
    fmt::println("Last time modified: {:%Y-%m-%d %H:%M:%S}", p);
    std::string extension = file.extension().string();
    auto image = sf::Image();
    if(!image.loadFromFile(file.string())){
        fmt::println("invalid file - loadFromFile() failed");
        exit(-1);
    }

    //no switch case for string :c
    if(extension == ".bmp"){
        fmt::println("Extension: {} - The BMP file format or bitmap,\nis a raster graphics image file format used to store bitmap digital images, independently of the display device\n(such as a graphics adapter), especially on Microsoft Windows[2] and OS/2[3] operating systems.", file.extension().string());
        display_image_info(image);
    }
    else if(extension == ".png") {
        fmt::println("decompressing PNG file");
        display_image_info(image);
    }
    else if(extension == ".tga"){
        fmt::println("decompressing TGA file");
        display_image_info(image);
    }
    else if(extension == ".jpg"){
        fmt::println("decompressing jpg file");
        display_image_info(image);
    }
    else if(extension == ".gif"){
        fmt::println("decompressing gif file");
        display_image_info(image);
    }
    else if(extension == ".psd"){
        fmt::println("decompressing psd file");
        display_image_info(image);
    }
    else if(extension == ".hdr"){
        fmt::println("decompressing hdr file");
        display_image_info(image);
    }
    else if(extension == ".pic"){
        fmt::println("decompressing TGA file");
        display_image_info(image);
    }
    else if(extension == ".tga"){
        fmt::println("decompressing TGA file");
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
            handle_file_extension(path);
        }

    }




    return 0;
}
