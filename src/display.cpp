#include "display.h"
#include "errors.h"

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_image.h>

#include <spdlog/spdlog.h>

#include <exception>
#include <iostream>
#include <string>

Display::Display(const char* window_name, Uint32 flags) {
    if (SDL_Init(flags) != 0) throw InitError();

    if (SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &m_window,
                                    &m_renderer) != 0)
        throw InitError();
    SDL_SetWindowTitle(m_window, window_name);
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags)) throw InitError();
}

Display::~Display() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void Display::draw() {
    // Clear the window with a black background
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    for (auto& texture : m_textures) {
        SDL_RenderCopy(m_renderer, texture, NULL, NULL);
    }

    // Show the window
    SDL_RenderPresent(m_renderer);
}

bool Display::add_image(std::string path) {
    spdlog::info("Start loading image {0}", path.c_str());
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == nullptr) {
        spdlog::error("SDL_image Error: {0}", IMG_GetError());
        return false;
    } else {
        m_textures.push_back(
            SDL_CreateTextureFromSurface(m_renderer, loaded_surface));
        SDL_FreeSurface(loaded_surface);
    }
    return true;
}
