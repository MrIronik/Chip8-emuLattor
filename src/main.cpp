#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <cstdint>

#include "window.hpp"

std::array<bool, DISPLAY_height * DISPLAY_width> display; // Should bd in chip8 class

int main(int argc, char *argv[])
{
    Window window;

    while (window.is_running_)
    {
        window.event();

        for (auto &pixel : display)
        {
            pixel = !pixel;
            window.update(display);
            window.render();
        }
    }

    return 0;
}