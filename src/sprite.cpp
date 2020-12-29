#include "sprite.h"

#include "errors.h"

#include <spdlog/spdlog.h>

Sprite::Sprite(std::string res_name, SDL_Rect rect) {
    spdlog::debug("Start loading image {0}", res_name.c_str());
    m_surface = IMG_Load(res_name.c_str());
    if (m_surface == nullptr) {
        throw SDLImgError("Resource not found");
    }
    m_rect = rect;
    m_texture = nullptr;
}

Sprite::~Sprite() { SDL_FreeSurface(m_surface); }

bool Sprite::render(SDL_Renderer* renderer) {
    if (m_texture == nullptr) {
        m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
    }
    SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);
    return true;
}
