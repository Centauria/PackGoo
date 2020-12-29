#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Sprite {
    SDL_Surface* m_surface;
    SDL_Rect m_rect;
    SDL_Texture* m_texture;

public:
    Sprite(std::string res_name, SDL_Rect rect);
    virtual ~Sprite();
    bool render(SDL_Renderer* renderer);
};
