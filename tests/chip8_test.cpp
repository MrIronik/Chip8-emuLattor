#include <gtest/gtest.h>
#include "chip8.hpp"


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

    for (auto address : chip.getStack())
    {
        EXPECT_EQ(address, 0);

    }

    for (auto reg : chip.getV())
    {
        EXPECT_EQ(reg, 0);
    }

    int counter = 0;
    for (auto address : chip.getMemory())
    {
        if (counter < FONTSET_size)
        {
            EXPECT_EQ(address, fontset.at(counter));
        } else
        {
            EXPECT_EQ(address, 0);
        }
        
        counter++;
    }
}

TEST(Chip8_Opcode_Test, OP_0x00E0)
{
    Chip8 chip;
    chip.init();
    // TODO: First load .ch8 file that write screen, useless test for now
    chip.load("../tests/test_roms/OP_Test_0x00E0.ch8");

    chip.emulateCycle();

    for (auto pixel : chip.getGfx())
    {
        EXPECT_EQ(pixel, 0);
    }
}