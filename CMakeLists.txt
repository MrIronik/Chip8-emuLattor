cmake_minimum_required(VERSION 3.20)
project(Chip8-emuLattor)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL3 REQUIRED)

add_executable(emuLattor
    src/main.cpp
    src/chip8/chip8.cpp
    src/platform/window.cpp
)

target_include_directories(emuLattor 
    PRIVATE
        src/platform
        src/chip8
)

target_link_libraries(emuLattor
    PRIVATE
        SDL3::SDL3
)