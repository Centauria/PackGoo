#include "display.h"
#include "sprite.h"
#include "errors.h"

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_image.h>

#include <spdlog/spdlog.h>

#include <exception>
#include <iostream>
#include <string>

Display::Display(const char* window_name, int width, int height,
                 bool fullscreen) {
    if (fullscreen) {
        if (SDL_CreateWindowAndRenderer(
                width, height,
                SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP |
                    SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI,
                &m_window, &m_renderer) != 0)
            throw SDLError();
    } else {
        if (SDL_CreateWindowAndRenderer(
                width, height,
                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI,
                &m_window, &m_renderer) != 0)
            throw SDLError();
    }
    SDL_SetWindowTitle(m_window, window_name);
}

Display::~Display() {
    for (auto const& sprite : m_sprites) {
        delete sprite;
    }
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void Display::draw() {
    // Clear the window with a black background
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    for (auto& sprite : m_sprites) {
        sprite->render(m_renderer);
    }

    // Show the window
    SDL_RenderPresent(m_renderer);
}

bool Display::add_sprite(Sprite* sprite) {
    m_sprites.push_back(sprite);
    return true;
}
