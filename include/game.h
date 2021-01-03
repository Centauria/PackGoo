#pragma once
#include <sol/sol.hpp>

#include "display.h"
#include "pool.h"

class Game {
    const char* NAME = "Perfect Delivery";

public:
    Game();
    virtual ~Game();
    bool initialize();
    void run();
    void loop();
    void exit();

private:
    void generate_config();
    void process_input();
    void update();
    void generate_output();
    Display* m_display_;
    volatile bool m_running_;
    Pool<void*> m_pool_;
    sol::state m_lua_;
    SDL_Event m_current_event_;
};
