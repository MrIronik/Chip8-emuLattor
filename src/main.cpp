#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <cstdint>

#include "window.hpp"
#include "chip8.hpp"

Window window;
Chip8 chip;

int main(int argc, char *argv[])
{
    chip.init();
    chip.load("test");

    while (window.is_running_)
    {
        window.event();

        chip.emulateCycle();

        


        if (chip.draw_flag)
        {
            window.update(chip.gfx);
            window.render();
        }
    }

    return 0;
}