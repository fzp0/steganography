#pragma once
#include <iostream>
#include <filesystem>
#include <chrono>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <SFML/Graphics/Image.hpp>


class info_grabber {
public:
    static void display_image_info(const std::filesystem::path& file);
    static void print_image_width_height(const sf::Image& image);
};