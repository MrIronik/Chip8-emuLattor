#include "chip8.hpp"
#include <gtest/gtest.h>

class Chip8_Basic_Test : public ::testing::Test {
protected:
    Chip8 chip;

    void SetUp() override {
        chip.init();
    }
};

class Chip8_Opcode_Test : public ::testing::Test {
protected:
    Chip8 chip;

    void SetUp() override {
        chip.init();
    }  
};