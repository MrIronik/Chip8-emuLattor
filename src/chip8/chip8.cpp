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
    (void)path_to_file; // TODO: Implement picking and openinge the file. Propably from terminal input

    std::ifstream rom("../ROMS/chip8-logo.ch8", std::ios::binary);

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
        for (auto &pixel : gfx)
        {
            pixel = 0;
        }
        program_counter += 2;
        break;

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