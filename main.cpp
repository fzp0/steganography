#include "info_grabber.h"
#include "image_writer.h"

void print_help(){
    fmt::println("--- Steganography ---");
    fmt::println("Program for hiding a string of text inside an image.");
    fmt::println("Supported image types: .bmp .png .tga .jpg/.jpeg .gif .psd .hdr .pic .pnm");
    fmt::println("-- Program flags --");
    fmt::println("Syntax: flag [alias] (argument1) (argument2) ... : description");
    fmt::println("-h [-help] : Displays this menu");
    fmt::println("-i [-info] (path) : Displays info about the specified file");
    fmt::println("-e [-encrypt] (path) (message) : Encrypts a message in the specified file");
    fmt::println("-d [-decrypt] (path) : Decrypts a message from the specified file");
    fmt::println("-c [-check] (path) : Checks if a message can be encrypted inside the specified file");
}

int main(int argc, char** argv) {
    // handle arguments
    if(argc <= 1) {
        print_help();
        return -1;
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
            info_grabber::display_image_info(path);
        }

    }
    else if(flag == "-c" || flag == "-check"){
        if(argc != 4){
            fmt::println("Invalid argument count.");
            return -1;
        }

        auto path = std::filesystem::path(argv[2]);
        if(!std::filesystem::exists(path)) {
            fmt::println("File at the specified path doesn't exist");
            return 0;
        }
        else {
            std::string message = argv[3];
            if(image_writer::is_write_possible(path,message)) {
                fmt::println("The message \"{}\" can and is able to be hidden inside this image.", message);
            }
        }
    }else if(flag == "-e" || flag == "-encrypt") {
        if(argc != 4){
            fmt::println("Invalid argument count.");
            return -1;
        }

        auto path = std::filesystem::path(argv[2]);
        if(!std::filesystem::exists(path)) {
            fmt::println("File at the specified path doesn't exist");
            return 0;
        }
        else {
            std::string message = argv[3];
            image_writer::write_message(path,message);
        }
    }else if(flag == "-d" || flag == "-decrypt"){
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
            image_writer::read_message(path);
        }
    }else{
        fmt::println("Unsupported arguments, run the program with the -h flag to see available options.");
        return -1;
    }



    return 0;
}
