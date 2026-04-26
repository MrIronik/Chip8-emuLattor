#pragma once

#include <SDL3/SDL.h>

class Window {

public:

    Window();
    ~Window();

    void run();


private:

    SDL_Window* window_{};

    SDL_Renderer* renderer_{};

    bool window_is_running_ {false};

};