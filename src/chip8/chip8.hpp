#pragma once

#include <cstdint>
#include <vector>

/* Constas Parameters */
static constexpr short SCREEN_width = 64;
static constexpr short SCREEN_hight = 32;
static constexpr short FONTSET_size = (5 * 16);
static constexpr short PROGRAM_start = 0x200;   // 512

static constexpr short MEMORY_size = 4096;
static constexpr short CPU_registers_number = 16;
static constexpr short CPU_stack_size = 16;
static constexpr short KEYPAD_size = 16;

const static std::array<uint8_t, FONTSET_size> fontset = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Chip8
{

private:
    /* Virtual Hardware */
    uint16_t opcode;

    std::array<uint8_t, MEMORY_size> memory;

    std::array<uint8_t, CPU_registers_number> V;

    uint16_t I;                  // index register
    uint16_t program_counter;

    uint8_t delay_timer;
    uint8_t sound_timer;

    std::array<uint16_t, CPU_stack_size> stack;
    uint16_t stack_pointer;

    std::array<uint16_t, KEYPAD_size> key;

    bool draw_flag;                                       // update window
    std::array<uint8_t, SCREEN_width * SCREEN_hight> gfx; // screen buffer


    /* Callback opcode */
    void OP_0x00E0_Handler(void);

public:
    /* Init chip8 and setup for emulation */
    void init();
    void load(const std::string& path_to_file);

    /* Emulation goes brrrrr */
    void emulateCycle();

    /* Some sweet user imputs */
    void setKeys();

    /* Getter functions */
    uint16_t getOpcode();

    std::array<uint8_t, MEMORY_size> getMemory() const;

    std::array<uint8_t, CPU_registers_number> getV() const;

    uint16_t getIndex_register();   // index register
    uint16_t getProgram_counter();

    uint8_t getDelay_timer();
    uint8_t getSound_timer();

    std::array<uint16_t, CPU_stack_size> getStack() const;
    uint16_t getStack_pointer();

    std::array<uint16_t, KEYPAD_size> getkey() const;

    bool getDraw_flag();
    std::array<uint8_t, SCREEN_width * SCREEN_hight> getGfx() const;
};

/*                     MEMORY MAP
 *
 * 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
 * 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
 * 0x200-0xFFF - Program ROM and work RAM
 *
 */

/*                      OPCODES
 *
 *  [x] 00E0 - clear the screen
 *  [ ] 00EE - return from subroutine to address pulled from stack
 *  [ ] 0NNN - jump to native assembler subroutine at 0xNNN
 *  [ ] 1NNN - jump to address NNN
 *  [ ] 2NNN - push return address onto stack and call subroutine at address NNN
 *  [ ] 3XNN - skip next opcode if vX == NN 
 *  [ ] 4XNN - skip next opcode if vX != NN
 *  [ ] 5XY0 - skip next opcode if vX == vY
 *  [ ] 6XNN - set vX to NN
 *  [ ] 7XNN - add NN to vX
 *  [ ] 8XY0 - set vX to the value of vY
 *  [ ] 8XY1 - set vX to the result of bitwise vX OR vY
 *  [ ] 8XY2 - set vX to the result of bitwise vX AND vY 
 *  [ ] 8XY3 - set vX to the result of bitwise vX XOR vY
 *  [ ] 8XY4 - add vY to vX, vF is set to 1 if an overflow happened, to 0 if not, even if X=F!
 *  [ ] 8XY5 - subtract vY from vX, vF is set to 0 if an underflow happened, to 1 if not, even if X=F!
 *  [ ] 8XY6 - set vX to vY and shift vX one bit to the right, set vF to the bit shifted out, even if X=F!
 *  [ ] 8XY7 - set vX to the result of subtracting vX from vY, vF is set to 0 if an underflow happened, to 1 if not, even if X=F!
 *  [ ] 8XYE - set vX to vY and shift vX one bit to the left, set vF to the bit shifted out, even if X=F!
 *  [ ] 9XY0 - skip next opcode if vX != vY
 *  [ ] ANNN - set I to NNN
 *  [ ] CXNN - jump to address XNN + vX
 *  [ ] DXY0 - draw 8xN pixel sprite at position vX, vY with data starting at the address in I, I is not changed
 *  [ ] EX9E - skip next opcode if key in the lower 4 bits of vX is pressed
 *  [ ] EXA1 - skip next opcode if key in the lower 4 bits of vX is not pressed
 *  [ ] FX07 - set vX to the value of the delay timer
 *  [ ] FX0A - wait for a key pressed and released and set vX to it, in megachip mode it also updates the screen like clear
 *  [ ] FX15 - set delay timer to vX
 *  [ ] FX18 - set sound timer to vX, sound is played as long as the sound timer reaches zero
 *  [ ] FX1E - add vX to I
 *  [ ] FX29 - set I to the 5 line high hex sprite for the lowest nibble in vX
 *  [ ] FX33 - write the value of vX as BCD value at the addresses I, I+1 and I+2
 *  [ ] FX55 - write the content of v0 to vX at the memory pointed to by I, I is incremented by X+1
 *  [ ] FX65 - read the bytes from memory pointed to by I into the registers v0 to vX, I is incremented by X+1
 * 
 */