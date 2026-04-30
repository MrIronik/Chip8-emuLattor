#pragma once

#include <SDL3/SDL.h>
#include <array>

class Window {

public:
    /* Logic Variables */
    bool is_running_ { true };

    /* Constructor and destructor */
    Window();
    ~Window();


    /* Basic Event Functions */
    void event();

    /* Basic Display Functions*/
    void render();
    void update(std::array<bool, 64 * 32> buffor);

    /* Basic Sound Functions */

private:

    /* SDL Library Variables */
    SDL_Window* window_{};
    SDL_Renderer* renderer_{};
    SDL_Texture* texture_{};

    /* Display Variables */
    std::array<uint32_t, 64 * 32> pixels = { 0xFFFFFFFF };      // Basic set tu Black

    /* Keyboard Variables */

};