cmake_minimum_required(VERSION 3.25)
project(steganography)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)
FETCHCONTENT_MAKEAVAILABLE(fmt)

add_executable(steganography main.cpp
        read_picture.h
        read_picture.cpp
        dib_headers.h)
target_link_libraries(steganography fmt)

