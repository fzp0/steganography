#include <iostream>
#include <fmt/core.h>



int main(int argc, char** argv) {
    // handle arguments
    if(argc <= 1) {
        fmt::println("Too few program arguments, execute program with -h to see options");
    }


    const std::string flag = argv[1];

    if(flag == "-h" || flag == "-help") {
        fmt::println("--- Steganography ---");
        fmt::println("Program for hiding a string of text inside an image.");
        fmt::println("Supported image types: .bmp .ppm");
        fmt::println("-- Program flags --");
        fmt::println("Syntax: flag [alias] (argument1) (argument2) ... : description");
        fmt::println("-h [-help] : Displays this menu");
        fmt::println("-e [-encrypt] (path) (message) : Encrypts a message in the specified file");
    }




    return 0;
}
