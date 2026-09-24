#include <gtest/gtest.h>
#include "chip8.hpp"

#define TEST_ROM_PATH(rom_name)    "test_roms/" rom_name

/* Basic Functions Tests */
TEST(Chip8_Basic_Test, Init)
{
    Chip8 chip;
    chip.init();

    EXPECT_EQ(chip.getProgram_counter(), 0x200);
    EXPECT_EQ(chip.getOpcode(), 0);
    EXPECT_EQ(chip.getIndex_register(), 0);
    EXPECT_EQ(chip.getStack_pointer(), 0);
    EXPECT_EQ(chip.getDelay_timer(), 0);
    EXPECT_EQ(chip.getSound_timer(), 0);

    for (auto pixel : chip.getGfx())
    {
        EXPECT_EQ(pixel, 0);
    }

    for (auto byte : chip.getStack())
    {
        EXPECT_EQ(byte, 0);

    }

    for (auto reg : chip.getV())
    {
        EXPECT_EQ(reg, 0);
    }

    int counter = 0;
    for (auto byte : chip.getMemory())
    {
        if (counter < FONTSET_size)
        {
            EXPECT_EQ(byte, fontset.at(counter));
        } else
        {
            EXPECT_EQ(byte, 0);
        }
        
        counter++;
    }
}
TEST(Chip8_Basic_Test, Load)
{
    Chip8 chip;
    size_t counter = 0;

    chip.init();
    chip.load(TEST_ROM_PATH("Load.ch8"));

    for (auto byte : chip.getMemory())
    {
        if (counter < FONTSET_size)
        {
            EXPECT_EQ(byte, fontset.at(counter));
        } else if (counter < PROGRAM_start)
        {
            EXPECT_EQ(byte, 0x00);
        } else
        {
            EXPECT_EQ(byte, 0x01);
        }

        if (byte != 0x00 && byte != 0x01)
            std::cout << counter << std::endl;

        ++counter;
    }
}

// TEST(Chip8_Basic_Test, EmulateCycle)
// {}

// TEST(Chip8_Basic_Test, SetKeys)
// {}


/* OPCODE Tests */

// TODO: First load .ch8 file that write screen, useless test for now
TEST(Chip8_Opcode_Test, OP_0x00E0)
{
    Chip8 chip;
    chip.init();

    chip.load(TEST_ROM_PATH("OP_0x00E0.ch8"));

    chip.emulateCycle();

    for (auto pixel : chip.getGfx())
    {
        EXPECT_EQ(pixel, 0);
    }
}

// TEST(Chip8_Opcode_Test, OP_0x00EE)
// {}

// TEST(Chip8_Opcode_Test, OP_0x0NNN)
// {}

// TEST(Chip8_Opcode_Test, OP_0x1NNN)
// {}

// TEST(Chip8_Opcode_Test, OP_0x2NNN)
// {}

// TEST(Chip8_Opcode_Test, OP_0x3XNN)
// {}

// TEST(Chip8_Opcode_Test, OP_0x4XNN)
// {}

// TEST(Chip8_Opcode_Test, OP_0x5XY0)
// {}

// TEST(Chip8_Opcode_Test, OP_0x6XNN)
// {}

// TEST(Chip8_Opcode_Test, OP_0x7XNN)
// {}

// TEST(Chip8_Opcode_Test, OP_0x8XY0)
// {}

// TEST(Chip8_Opcode_Test, OP_0x8XY1)
// {}

// TEST(Chip8_Opcode_Test, OP_0x8XY2)
// {}

// TEST(Chip8_Opcode_Test, OP_0x8XY3)
// {}

// TEST(Chip8_Opcode_Test, OP_0x8XY4)
// {}

// TEST(Chip8_Opcode_Test, OP_0x8XY5)
// {}

// TEST(Chip8_Opcode_Test, OP_0x8XY6)
// {}

// TEST(Chip8_Opcode_Test, OP_0x8XY7)
// {}

// TEST(Chip8_Opcode_Test, OP_0x8XYE)
// {}

// TEST(Chip8_Opcode_Test, OP_0x9XY0)
// {}

// TEST(Chip8_Opcode_Test, OP_0xANNN)
// {}

// TEST(Chip8_Opcode_Test, OP_0xCXNN)
// {}

// TEST(Chip8_Opcode_Test, OP_0xDXY0)
// {}

// TEST(Chip8_Opcode_Test, OP_0xEX9E)
// {}

// TEST(Chip8_Opcode_Test, OP_0xEXA1)
// {}

// TEST(Chip8_Opcode_Test, OP_0xFX07)
// {}

// TEST(Chip8_Opcode_Test, OP_0xFX0A)
// {}

// TEST(Chip8_Opcode_Test, OP_0xFX15)
// {}

// TEST(Chip8_Opcode_Test, OP_0xFX18)
// {}

// TEST(Chip8_Opcode_Test, OP_0xFX1E)
// {}

// TEST(Chip8_Opcode_Test, OP_0xFX29)
// {}

// TEST(Chip8_Opcode_Test, OP_0xFX33)
// {}

// TEST(Chip8_Opcode_Test, OP_0xFX55)
// {}

// TEST(Chip8_Opcode_Test, OP_0xFX65)
// {}
