#include "image_writer.h"
#include <fmt/core.h>
#include <SFML/Graphics/Image.hpp>


bool image_writer::is_write_possible(const std::filesystem::path &file, std::string message) {

        auto image = sf::Image();
        if(!image.loadFromFile(file.string())){
                fmt::println("invalid file - loadFromFile() failed");
                return false;
        }

        auto image_size = image.getSize();

        if((image_size.x * image_size.y - 32) / 8 < message.size()) {
                fmt::println("File is too small to hide \"{}\", this message needs an image with at least {} pixels", message, message.size()*8 + 32);
                return false;
        }

        return true;
}

void image_writer::write_message(const std::filesystem::path &file, std::string &message) {
        if(!is_write_possible(file,message))
                return;

        auto image = sf::Image();
        image.loadFromFile(file.string());
        auto image_size = image.getSize();

        int pixel_count = image_size.x * image_size.y;


        int step = (pixel_count-32) / message.size() / 8;
        int current_pixel = 0;


        fmt::println("Hiding the message...", pixel_count, step);
        //fmt::println("loaded image, pixel_count: {} , step: {} ", pixel_count, step);

        for(int i = 0; i< 32;i++){ // in the first 32 pixels we hide the message size
            auto pixel_color = image.getPixel(current_pixel % image_size.x, current_pixel / image_size.x);
            //fmt::println("color before: {} {} {}", pixel_color.r, pixel_color.g, pixel_color.b);
            switch(current_pixel % 3) {
                case 0:
                    message.size() & (1 << i) ? pixel_color.r |= 1 : pixel_color.r &= ~(1);
                    break;
                case 1:
                    message.size() & (1 << i) ? pixel_color.g |= 1 : pixel_color.g &= ~(1);
                    break;
                case 2:
                    message.size() & (1 << i) ? pixel_color.b |= 1 : pixel_color.b &= ~(1);
                    break;
            }
            //fmt::println("color after: {} {} {}", pixel_color.r, pixel_color.g, pixel_color.b);
            image.setPixel(current_pixel % image_size.x, current_pixel / image_size.x, pixel_color);
            current_pixel+=1;
        }

        for(auto msg_iter = message.begin(); msg_iter != message.end(); msg_iter++) { // through every char
                //fmt::println("writing \'{}\'",*msg_iter);
                for(int current_bit = 0; current_bit < 8; current_bit++) { // and each bit in the char
                        //fmt::println("bit: {} , x: {} , y: {}", current_bit, current_pixel % image_size.x, current_pixel / image_size.x);
                        auto pixel_color = image.getPixel(current_pixel % image_size.x, current_pixel / image_size.x); // we grab the pixel color
                        //fmt::println("color before: {} {} {}", pixel_color.r, pixel_color.g, pixel_color.b);
                        switch(current_pixel % 3) { // and modify the last bit of a chosen component (last bit so it doesn't change the image much visually!)
                                case 0:
                                        *msg_iter & (1 << current_bit) ? pixel_color.r |= 1 : pixel_color.r &= ~(1);
                                        break;
                                case 1:
                                        *msg_iter & (1 << current_bit) ? pixel_color.g |= 1 : pixel_color.g &= ~(1);
                                        break;
                                case 2:
                                        *msg_iter & (1 << current_bit) ? pixel_color.b |= 1 : pixel_color.b &= ~(1);
                                        break;
                        }
                        //fmt::println("color after: {} {} {}", pixel_color.r, pixel_color.g, pixel_color.b);
                        image.setPixel(current_pixel % image_size.x, current_pixel / image_size.x, pixel_color);
                        current_pixel+=step;
                }
        }

        if(!image.saveToFile(file.string())) {
                fmt::println("saveToFile() failed");
                exit(-1);
        }

        fmt::println("Successfully hidden the message inside the picture");
}

void image_writer::read_message(const std::filesystem::path &file) {
    if(!is_write_possible(file,""))
        return;

    fmt::println("Searching for the hidden message...");

    auto image = sf::Image();
    image.loadFromFile(file.string());
    auto image_size = image.getSize();

    int pixel_count = image_size.x * image_size.y;
    int current_pixel = 0;
    int message_size = 0;
    for (int i = 0; i < 32; i++) {
        auto pixel_color = image.getPixel(current_pixel % image_size.x, current_pixel / image_size.x);
        //fmt::println("color before: {} {} {}", pixel_color.r, pixel_color.g, pixel_color.b);
        switch (current_pixel % 3) {
            case 0:
                pixel_color.r & 1 ? message_size |= (1 << i) : message_size &= ~(1 << i);
                break;
            case 1:
                pixel_color.g & 1 ? message_size |= (1 << i) : message_size &= ~(1 << i);
                break;
            case 2:
                pixel_color.b & 1 ? message_size |= (1 << i) : message_size &= ~(1 << i);
                break;
        }
        //fmt::println("color after: {} {} {}", pixel_color.r, pixel_color.g, pixel_color.b);
        image.setPixel(current_pixel % image_size.x, current_pixel / image_size.x, pixel_color);
        current_pixel++;
    }


    int step = (pixel_count - 32) / message_size / 8;

    std::string message = "";
    for(int current_char = 0; current_char < message_size; current_char++){
        char c = 0;
        for(int bit_in_char = 0; bit_in_char < 8; bit_in_char++){
            auto pixel_color = image.getPixel(current_pixel % image_size.x, current_pixel / image_size.x);
            switch (current_pixel % 3) {
                case 0:
                    pixel_color.r & 1 ? c |= (1 << bit_in_char) : c &= ~(1 << bit_in_char);
                    break;
                case 1:
                    pixel_color.g & 1 ? c |= (1 << bit_in_char) : c &= ~(1 << bit_in_char);
                    break;
                case 2:
                    pixel_color.b & 1 ? c |= (1 << bit_in_char) : c &= ~(1 << bit_in_char);
                    break;
            }
            current_pixel+=step;
        }
        message+=c;
    }

    fmt::println("The hidden message is: {}",message);
}

