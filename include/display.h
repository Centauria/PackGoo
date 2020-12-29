#include <SDL.h>
#include <string>
#include <vector>

#include "sprite.h"

class Display {
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::vector<Sprite*> m_sprites;

public:
    Display(const char* window_name, Uint32 flags = SDL_INIT_EVERYTHING);
    virtual ~Display();
    void draw();
    bool add_sprite(Sprite*);
};
