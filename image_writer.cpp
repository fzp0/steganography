//
// Created by e on 04.06.2024.
//

#include "image_writer.h"
#include <fmt/core.h>
#include <SFML/Graphics/Image.hpp>


bool image_writer::is_write_possible(const std::filesystem::path &file, std::string& message) {

        auto image = sf::Image();
        if(!image.loadFromFile(file.string())){
                fmt::println("invalid file - loadFromFile() failed");
                return false;
        }

        auto image_size = image.getSize();

        if(image_size.x * image_size.y / 8 < message.size()) {
                fmt::println("Image is too small to write \"{}\", this message needs at least {} pixels", message, message.size()*8);
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
        int step = pixel_count / message.size() / 8;
        int current_pixel = 0;


        fmt::println("Hiding the message...", pixel_count, step);
        //fmt::println("loaded image, pixel_count: {} , step: {} ", pixel_count, step);

        for(auto msg_iter = message.begin(); msg_iter != message.end(); msg_iter++) { // through every char
                //fmt::println("writing \'{}\'",*msg_iter);
                for(int current_bit = 0; current_bit < 8; current_bit++) { // and each bit in the char
                        //fmt::println("bit: {} , x: {} , y: {}", current_bit, current_pixel % image_size.x, current_pixel / image_size.x);
                        auto pixel_color = image.getPixel(current_pixel % image_size.x, current_pixel / image_size.x); // we grab the pixel color
                        //fmt::println("color before: {} {} {}", pixel_color.r, pixel_color.g, pixel_color.b);
                        switch(current_pixel % 3) { // and modify the last bit of a chosen component (last bit so it doesn't change the image much!)
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
        auto image = sf::Image();
        image.loadFromFile(file.string());
        auto image_size = image.getSize();

        int pixel_count = image_size.x * image_size.y;
        int step = pixel_count / message.size() / 8;
        int current_pixel = 0;
}

