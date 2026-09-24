#include <gtest/gtest.h>
#include "chip8.hpp"

#define TEST_ROM(rom_name) "test_roms/" rom_name ".ch8"

/* Basic Functions Tests */
TEST(Chip8_Basic_Test, Init)
{
    Chip8 chip;
    chip.init();

    EXPECT_EQ(chip.getProgram_counter(), PROGRAM_start);
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
        }
        else
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
    chip.load(TEST_ROM("Load"));

    for (auto byte : chip.getMemory())
    {
        if (counter < FONTSET_size)
        {
            EXPECT_EQ(byte, fontset.at(counter));
        }
        else if (counter < PROGRAM_start)
        {
            EXPECT_EQ(byte, 0x00);
        }
        else
        {
            EXPECT_EQ(byte, 0x01);
        }

        if (byte != 0x00 && byte != 0x01)
            std::cout << counter << std::endl;

        ++counter;
    }
}

TEST(Chip8_Basic_Test, DISABLED_EmulateCycle)
{}

TEST(Chip8_Basic_Test, DISABLED_SetKeys)
{}

/* OPCODE Tests */

// TODO: First load .ch8 file that write screen, useless test for now
TEST(Chip8_Opcode_Test, OP_0x00E0)
{
    Chip8 chip;
    constexpr short expected_pc = PROGRAM_start + 2;

    chip.init();
    chip.load(TEST_ROM("OP_0x00E0"));

    chip.emulateCycle();

    for (auto pixel : chip.getGfx())
    {
        EXPECT_EQ(pixel, 0);
    }

    EXPECT_EQ(chip.getProgram_counter(), expected_pc);
}

TEST(Chip8_Opcode_Test, OP_0x00EE)
{
    Chip8 chip;
    constexpr uint16_t exp_pc = 0x202;
    constexpr uint16_t exp_sp = 1;
    constexpr uint16_t exp_fill_sp = 0;
    constexpr uint16_t exp_st = 0x202;

    chip.init();
    chip.load(TEST_ROM("OP_0x00EE"));

    chip.emulateCycle();    // Store pc in stack]
    EXPECT_EQ(chip.getStack_pointer(), exp_sp);
    EXPECT_EQ(chip.getStack().at(exp_fill_sp), exp_st);

    chip.emulateCycle();    // Return from subroutine
    EXPECT_EQ(chip.getStack_pointer(), exp_fill_sp);
    EXPECT_EQ(chip.getStack().at(exp_fill_sp), 0x00);
    EXPECT_EQ(chip.getProgram_counter(), exp_pc);
}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x0NNN)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x1NNN)
{}

TEST(Chip8_Opcode_Test, OP_0x2NNN)
{
    Chip8 chip;
    constexpr uint16_t exp_pc = 0x222;
    constexpr uint16_t exp_st = 0x202;
    constexpr uint16_t exp_sp = 1;
    
    chip.init();
    chip.load(TEST_ROM("OP_0x2NNN"));

    chip.emulateCycle();

    EXPECT_EQ(chip.getProgram_counter(), exp_pc);
    EXPECT_EQ(chip.getStack().at(exp_sp - 1), exp_st);
    EXPECT_EQ(chip.getStack_pointer(), exp_sp);
}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x3XNN)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x4XNN)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x5XY0)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x6XNN)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x7XNN)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x8XY0)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x8XY1)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x8XY2)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x8XY3)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x8XY4)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x8XY5)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x8XY6)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x8XY7)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x8XYE)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0x9XY0)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xANNN)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xCXNN)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xDXY0)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xEX9E)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xEXA1)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX07)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX0A)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX15)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX18)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX1E)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX29)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX33)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX55)
{}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX65)
{}
