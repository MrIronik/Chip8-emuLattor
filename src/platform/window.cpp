#include "window.hpp"

#include <stdexcept>
#include <thread>
#include <chrono>

Window::Window()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        throw std::runtime_error("SDL_Init failed");

    window_ = SDL_CreateWindow(
        "emuLattor", 
        640,        // 10x times orginal resolution
        320,        // 10x times orginal resolution
        SDL_WINDOW_RESIZABLE);

    if (!window_) throw std::runtime_error("Window failed");

    renderer_ = SDL_CreateRenderer(window_, nullptr);

    if (!renderer_) throw std::runtime_error("Rendered failed");

    texture_ = SDL_CreateTexture(
        renderer_,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        64,
        32
    );

    if (!texture_) throw std::runtime_error("Texture failed");
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_DestroyTexture(texture_);
    SDL_Quit();
}

void Window::event()
{
    SDL_Event event;


    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) is_running_ = false;
        }

}

void Window::render()
{
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

        SDL_RenderClear(renderer_);

        SDL_RenderTexture(renderer_, texture_, NULL, NULL);

        SDL_RenderPresent(renderer_);

        SDL_Delay(1);

}

void Window::update(std::array<bool, 64 * 32> buffor)
{
    static constexpr uint32_t WHITE_PIXEL = 0xFFFFFFFF;
    static constexpr uint32_t BLACK_PIXEL = 0x000000FF;

    for (uint32_t i = 0; i < pixels.size(); i++) {
        if (buffor.at(i)) {
            pixels.at(i) = WHITE_PIXEL;
        } else {
            pixels.at(i) = BLACK_PIXEL;
        }
    }

    SDL_UpdateTexture(texture_, NULL, pixels.data(), 64 * sizeof(uint32_t));
}
