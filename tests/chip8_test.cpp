#include "chip8.hpp"
#include "fixture.hpp"
#include <cstdint>
#include <gtest/gtest.h>

#define TEST_ROM(rom_name) "test_roms/" rom_name ".ch8"

/* Basic Functions Tests */
TEST_F(Chip8_Basic_Test, Init) {
  EXPECT_EQ(chip.getProgram_counter(), PROGRAM_start);
  EXPECT_EQ(chip.getOpcode(), 0);
  EXPECT_EQ(chip.getIndex_register(), 0);
  EXPECT_EQ(chip.getStack_pointer(), 0);
  EXPECT_EQ(chip.getDelay_timer(), 0);
  EXPECT_EQ(chip.getSound_timer(), 0);

  for (auto pixel : chip.getGfx()) {
    EXPECT_EQ(pixel, 0);
  }

  for (auto byte : chip.getStack()) {
    EXPECT_EQ(byte, 0);
  }

  for (auto reg : chip.getV()) {
    EXPECT_EQ(reg, 0);
  }

  int counter = 0;
  for (auto byte : chip.getMemory()) {
    if (counter < FONTSET_size) {
      EXPECT_EQ(byte, fontset.at(counter));
    } else {
      EXPECT_EQ(byte, 0);
    }

    counter++;
  }
}

TEST_F(Chip8_Basic_Test, Load) {
  size_t counter = 0;

  chip.load(TEST_ROM("Load"));

  for (auto byte : chip.getMemory()) {
    if (counter < FONTSET_size) {
      EXPECT_EQ(byte, fontset.at(counter));
    } else if (counter < PROGRAM_start) {
      EXPECT_EQ(byte, 0x00);
    } else {
      EXPECT_EQ(byte, 0x01);
    }

    if (byte != 0x00 && byte != 0x01)
      std::cout << counter << std::endl;

    ++counter;
  }
}

TEST_F(Chip8_Basic_Test, DISABLED_EmulateCycle) {}

TEST_F(Chip8_Basic_Test, DISABLED_SetKeys) {}

/* OPCODE Tests */

// TODO: First load .ch8 file that write screen, useless test for now
TEST_F(Chip8_Opcode_Test, OP_0x00E0) {
  constexpr short expected_pc = PROGRAM_start + 2;

  chip.load(TEST_ROM("OP_0x00E0"));

  chip.emulateCycle();

  for (auto pixel : chip.getGfx()) {
    EXPECT_EQ(pixel, 0);
  }

  EXPECT_EQ(chip.getProgram_counter(), expected_pc);
}

TEST_F(Chip8_Opcode_Test, OP_0x00EE) {
  constexpr uint16_t exp_pc = 0x202;
  constexpr uint16_t exp_sp = 1;
  constexpr uint16_t exp_fill_sp = 0;
  constexpr uint16_t exp_st = 0x202;

  chip.load(TEST_ROM("OP_0x00EE"));

  chip.emulateCycle(); // Store pc in stack]
  EXPECT_EQ(chip.getStack_pointer(), exp_sp);
  EXPECT_EQ(chip.getStack().at(exp_fill_sp), exp_st);

  chip.emulateCycle(); // Return from subroutine
  EXPECT_EQ(chip.getStack_pointer(), exp_fill_sp);
  EXPECT_EQ(chip.getStack().at(exp_fill_sp), 0x00);
  EXPECT_EQ(chip.getProgram_counter(), exp_pc);
}

TEST_F(Chip8_Opcode_Test, OP_0x0NNN) {
  constexpr uint16_t exp_pc = 0x300;

  chip.load(TEST_ROM("OP_0X0NNN"));

  chip.emulateCycle();
  EXPECT_EQ(chip.getProgram_counter(), exp_pc);
}

TEST_F(Chip8_Opcode_Test, OP_0x1NNN) {
  constexpr uint16_t exp_pc = 0x300;

  chip.load(TEST_ROM("OP_0x1NNN"));
  chip.emulateCycle();
  EXPECT_EQ(chip.getProgram_counter(), exp_pc);
}

TEST_F(Chip8_Opcode_Test, OP_0x2NNN) {
  constexpr uint16_t exp_pc = 0x222;
  constexpr uint16_t exp_st = 0x202;
  constexpr uint16_t exp_sp = 1;

  chip.load(TEST_ROM("OP_0x2NNN"));

  chip.emulateCycle();

  EXPECT_EQ(chip.getProgram_counter(), exp_pc);
  EXPECT_EQ(chip.getStack().at(exp_sp - 1), exp_st);
  EXPECT_EQ(chip.getStack_pointer(), exp_sp);
}

TEST_F(Chip8_Opcode_Test, OP_0x3XNN) {
  constexpr uint16_t exp_pc_1 = 0x204;
  constexpr uint16_t exp_pc_2 = 0x20A;
  constexpr uint16_t exp_pc_3 = 0x210;
  constexpr uint16_t exp_pc_4 = 0x212;

  chip.load(TEST_ROM("OP_0x3XNN"));

  /* 1. Set V[0] to 10 */
  chip.emulateCycle();
  chip.emulateCycle(); // Check if V[0] is 5
  EXPECT_EQ(chip.getProgram_counter(), exp_pc_1);

  /* 2. Set V[1] to 20 */
  chip.emulateCycle();
  chip.emulateCycle(); // Check if V[1] is 20 (skip)
  EXPECT_EQ(chip.getProgram_counter(), exp_pc_2);

  /* 3. Set V[15] to 10 */
  chip.emulateCycle();
  chip.emulateCycle(); // Check if V[15] is 10 (skip)
  EXPECT_EQ(chip.getProgram_counter(), exp_pc_3);
}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x4XNN) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x5XY0) {}

TEST_F(Chip8_Opcode_Test, OP_0x6XNN) {
  uint16_t exp_pc = 0x202;

  chip.load(TEST_ROM("OP_0x6XNN"));

  for (int i = 0; i < 16; i++) {
    chip.emulateCycle();
    EXPECT_EQ(chip.getV().at(i), i);
    EXPECT_EQ(chip.getProgram_counter(), exp_pc);
    exp_pc += 0x02;
  }
}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x7XNN) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x8XY0) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x8XY1) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x8XY2) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x8XY3) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x8XY4) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x8XY5) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x8XY6) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x8XY7) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x8XYE) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0x9XY0) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xANNN) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xCXNN) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xDXY0) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xEX9E) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xEXA1) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xFX07) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xFX0A) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xFX15) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xFX18) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xFX1E) {}

TEST_F(Chip8_Opcode_Test, DISABLED_OP_0xFX29) {}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX33) {}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX55) {}

TEST(Chip8_Opcode_Test, DISABLED_OP_0xFX65) {}
