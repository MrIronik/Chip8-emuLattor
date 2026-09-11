#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <cstdint>

#include "window.hpp"


int main(int argc, char *argv[])
{
    Window window;

    std::array<uint8_t, WINDOW_width * WINDOW_height> display = {};

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