#include <SDL.h>
#include <string>
#include <vector>

class Display {
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    std::vector<SDL_Texture *> m_textures;

   public:
    Display(const char *window_name, Uint32 flags = SDL_INIT_EVERYTHING);
    virtual ~Display();
    void draw();
    bool add_image(std::string);
};
