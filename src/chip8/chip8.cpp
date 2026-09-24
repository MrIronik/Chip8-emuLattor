#include <cstdint>
#include <vector>
#include <fstream>

#include "chip8.hpp"

void Chip8::init()
{
    /* Set the default/starting values of chip8 */
    program_counter = 0x200;
    opcode = 0;
    I = 0;
    stack_pointer = 0;

    /* Clear screen buffer */
    for (auto &pixel : gfx)
    {
        pixel = 0;
    }

    /* Clear chip8's stack */
    for (auto &address : stack)
    {
        address = 0;
    }

    /* Clear CPU registers */
    for (auto &reg : V)
    {
        reg = 0;
    }

    /* Clear memory */
    for (auto &address : memory)
    {
        address = 0;
    }

    /* Load Fontset */
    for (short i = 0; i < FONTSET_size; i++)
    {
        memory.at(i) = fontset.at(i);
    }

    /* Reset Timer */
    // TODO: Implement timer reset!
    delay_timer = 0;
    sound_timer = 0;
}

void Chip8::load(const std::string path_to_file)
{
    // (void)path_to_file; // TODO: Implement picking and openinge the file. Propably from terminal input

    // std::ifstream rom("../ROMS/chip8-logo.ch8", std::ios::binary);
    std::ifstream rom(path_to_file, std::ios::binary);

    if (!rom)
    {
        std::runtime_error("Filed to open ROM\n");
        return;
    }

    rom.read(
        reinterpret_cast<char *>(memory.data() + 0x200),
        memory.size() - 0x200);
}

void Chip8::emulateCycle()
{
    /* Fetch opcode form memory */
    opcode = memory.at(program_counter) << 8 | memory.at(program_counter + 1);

    /* Decode opcode */
    // TODO: Man it will be looong switch, do something about it...
    switch (opcode & 0xF000)
    {
    case 0x00E0: // Clear screen
        OP_0x00E0_Handler();
        break;

    case 0x00EE: // return from subroutine to address pulled from stack
        

    case 0xA000:
        I = opcode & 0x0FFF;
        program_counter += 2;
        break;

    default:
        printf("Unknown opcode 0x%X\n", opcode);
        return;
    }

    if (delay_timer > 0)
    {
        --delay_timer;
    }

    if (sound_timer > 0)
    {
        --sound_timer;
    }
}

// void Chip8::setKeys();

/* Chip8 getter functions */
uint16_t Chip8::getOpcode()
{
    return opcode;
}

std::array<uint8_t, MEMORY_size> Chip8::getMemory() const
{
    return memory;
}

std::array<uint8_t, CPU_registers_number> Chip8::getV() const
{
    return V;
}

uint16_t Chip8::getIndex_register()
{
    return I;
}   // index register

uint16_t Chip8::getProgram_counter()
{
    return program_counter;
}

uint8_t Chip8::getDelay_timer()
{
    return delay_timer;
}

uint8_t Chip8::getSound_timer()
{
    return sound_timer;
}

std::array<uint16_t, CPU_stack_size> Chip8::getStack() const
{
    return stack;
}

uint16_t Chip8::getStack_pointer()
{
    return stack_pointer;
}

std::array<uint16_t, KEYPAD_size> Chip8::getkey() const
{
    return key;
}

bool Chip8::getDraw_flag()
{
    return draw_flag;
}

std::array<uint8_t, SCREEN_width * SCREEN_hight> Chip8::getGfx() const
{
    return gfx;
}

/* Chip8 OPCode Handler functions */

void Chip8::OP_0x00E0_Handler(void)
{
    for (auto &pixel : gfx)
        {
            pixel = 0;
        }
        program_counter += 2;
}