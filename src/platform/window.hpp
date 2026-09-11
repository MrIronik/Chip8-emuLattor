#pragma once

#include <SDL3/SDL.h>
#include <cstdint>
#include <vector>

class Window {

private:
    /* SDL Library Variables */
    SDL_Window* window_{};
    SDL_Renderer* renderer_{};
    SDL_Texture* texture_{};

    /* Display Variables */
    static constexpr uint32_t WHITE_PIXEL = 0xFFFFFFFF;
    static constexpr uint32_t BLACK_PIXEL = 0x000000FF;
    static constexpr short WINDOW_width = 64;
    static constexpr short WINDOW_height = 32;

    std::array<uint32_t, WINDOW_width * WINDOW_height> pixels = { 0xFFFFFFFF };      // Basic set tu Black

    /* Keyboard Variables */

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
    void update(std::array<uint8_t, WINDOW_width * WINDOW_height> buffor);

    /* Basic Sound Functions */

};