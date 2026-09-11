#pragma once

#include <cstdint>
#include <vector>

static constexp SCREEN_width = 64;
static constexp SCREEN_hight = 32;

class Chip8
{

private:
/* Constas Parameters */
static constexpr short MEMORY_size = 4096;
static constexpr short CPU_registers_number = 16;
static constexpr short CPU_stack_size = 16;
static constexpr short KEYPAD_size = 16;

/* Virtual Hardware */
static uint16_t opcode;

static std::array<uint8_t, MEMORY_size> memory;

static uint8_t V[CPU_registers_number];

static uint16_t index_register;
static uint16_t program_counter;

static uint8_t delay_timer;
static uint8_t sound_timer;

static std::array<uint16_t, CPU_stack_size> stack;
static uint16_t stack_pointer;

static std::array<uint16_t, KEYPAD_size> key;

public:
bool draw_flag;                                         // update window
std:array<uint8_t, SCREEN_width * SCREEN_hight> gfx;    // screen buffer

/* Init chip8 and setup for emulation */
void init();
void load(string path_to_file);

/* Emulation goes brrrrr */
void emulateCycle();

/* Some sweet user imputs */
setKeys();

}

/*                     MEMORY MAP
 *
 * 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
 * 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
 * 0x200-0xFFF - Program ROM and work RAM
 *
 */