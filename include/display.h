#pragma once
#include <SDL.h>
#include <string>
#include <vector>

#include "sprite.h"

class Display {
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::vector<Sprite*> m_sprites;

public:
    Display(const char* window_name, int width, int height, bool fullscreen);
    virtual ~Display();
    void draw();
    bool add_sprite(Sprite*);
};
