#pragma once
#include <filesystem>

class image_writer {
public:
    static bool is_write_possible(const std::filesystem::path& file, std::string message);
    static void write_message(const std::filesystem::path& file, std::string& message);
    static void read_message(const std::filesystem::path& file);
};

