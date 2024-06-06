cmake_minimum_required(VERSION 3.25)
project(steganography)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)


add_executable(steganography main.cpp
        info_grabber.h
        info_grabber.cpp
        image_writer.cpp
        image_writer.h
)
target_link_libraries(steganography fmt sfml-graphics)

