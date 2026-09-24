cmake_minimum_required(VERSION 3.20)
project(Chip8-emuLattor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include(FetchContent)

# FetchContent_Declare(
#     googletest
#     URL https://github.com/google/googletest/archive/refs/heads/main.zip
# )

# FetchContent_MakeAvailable(googletest)

find_package(SDL3 REQUIRED)
find_package(GTest REQUIRED)

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

# Tests

enable_testing()

add_executable(chip8_tests
    tests/chip8_test.cpp
    src/chip8/chip8.cpp
)

target_include_directories(chip8_tests
    PRIVATE
    src/chip8
)

target_link_libraries(chip8_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(chip8_tests)