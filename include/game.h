#pragma once
#include <SDL.h>

class Game {
public:
    Game();
    bool initialize();
    void loop();
    void exit();
private:
    void process_input();
    void update();
    void generate_output();
    SDL_Window* m_window_;
    bool m_running;
};
