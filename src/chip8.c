#include "chip8.c"
#include <stdint.h>

#define MEMORY_SIZE 4096
#define CPU_REGISTERS 15

#define SCREEN_HIGHT 32
#define SCREEN_HIDTH 64

#define STACK_SIZE 16

/* System Memory Map
 *
 * 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
 * 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
 * 0x200-0xFFF - Program ROM and work RAM
 * 
 */

uint16_t opcode;
uint8_t memory[MEMORY_SIZE];    // Memory
uint8_t V[CPU_REGISTERS];       // Cpu Registers
uint16_t index_register;
uint16_t program_counter;

uint8_t gfx[SCREEN_HIGHT * SCREEN_WIDTH];   // Representation of the screen

uint8_t delay_timer;
uint8_t sound_timer;

uint16_t stack[STACK_SIZE];
uint16_t stack_pointer;