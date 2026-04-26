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
        640, 
        320, 
        SDL_WINDOW_RESIZABLE);

    if (!window_) throw std::runtime_error("Window failed");

    renderer_ = SDL_CreateRenderer(window_, nullptr);

    if (!renderer_) throw std::runtime_error("Rendered failed");
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Window::run()
{

    window_is_running_ = true;
    SDL_Event event;

    bool change = true;

    while (window_is_running_)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                window_is_running_ = false;
        }

        if (change) {
            SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
            change = false;
        } else {
            SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
            change = true;
        }
        
        SDL_RenderClear(renderer_);

        SDL_FRect rect{100, 50, 200, 100};

        SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 100);
        SDL_RenderFillRect(renderer_, &rect);

        SDL_RenderPresent(renderer_);

        SDL_Delay(1);

    }
}