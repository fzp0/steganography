#include "info_grabber.h"

void info_grabber::print_image_width_height(const sf::Image &image) {
    auto sizevec = image.getSize();
    fmt::println("Image Width: {}, Image Height: {}", sizevec.x, sizevec.y);
}



void info_grabber::display_image_info(std::filesystem::path const &file) {

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
        print_image_width_height(image);
    }
    else if(extension == ".png") {
        fmt::println("Extension: .png - Portable Network Graphics (PNG) is a raster-graphics file format that supports lossless data compression.");
        print_image_width_height(image);
    }
    else if(extension == ".tga"){
        fmt::println("Extension: .tga - Truevision TGA, often referred to as TARGA, is a raster graphics file format created by Truevision Inc. (now part of Avid Technology). It was the native format of TARGA and VISTA boards, which were the first graphic cards for IBM-compatible PCs to support Highcolor/truecolor display. This family of graphic cards was intended for professional computer image synthesis and video editing with PCs; for this reason, usual resolutions of TGA image files match those of the NTSC and PAL video formats.");
        print_image_width_height(image);
    }
    else if(extension == ".jpg" || extension == ".jpeg"){
        fmt::println("Extension: .jpg/.jpeg - JPEG (short for Joint Photographic Experts Group) is a commonly used method of lossy compression for digital images, particularly for those images produced by digital photography.");
        print_image_width_height(image);
    }
    else if(extension == ".gif"){
        fmt::println("Extension: .gif - The Graphics Interchange Format (GIF) is a bitmap image format that was developed by a team at the online services provider CompuServe led by American computer scientist Steve Wilhite and released on June 15, 1987.");
        print_image_width_height(image);
    }
    else if(extension == ".psd"){
        fmt::println("Extension: .psd - PSD files are the native file format of Adobe Photoshop.");
        print_image_width_height(image);
    }
    else if(extension == ".hdr"){
        fmt::println("Extension: .hdr - The original Radiance picture format (typically .pic) is the basis for one of the standard HDR (High Dynamic Range image) image formats (.hdr), supported by most HDR image editors including Adobe PhotoShop (eg: PhotoShop CS2, 2006). Each pixel is stored as 4 bytes, one byte mantissa for each r,g,b and a shared one byte exponent. The pixel data may be stored uncompressed or using a straightforward run length encoding scheme.");
        print_image_width_height(image);
    }
    else if(extension == ".pic"){
        fmt::println("Extension: .pic - PICtor is an image file format developed by John Bridges, the principal author of PCPaint, the first Paintbrush program for the PC. It was also the native file format for Pictor Paint and Graphics Animation System for Professionals (GRASP) (also by Bridges) and became the first widely accepted DOS imaging standard.");
        print_image_width_height(image);
    }
    else if(extension == ".pnm"){
        fmt::println("Extension: .pnm - Simple uncompressed raster image file format, associated with the Netpbm library and suite of image processing utilities. It is designed so that it is straightforward for programmers to import and export them.");
        print_image_width_height(image);
    }
    else{
        fmt::println("Unsupported File Extension: {}", file.extension().string());
    }
}

