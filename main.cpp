#define SDL_MAIN_HANDLED

#include <sol/sol.hpp>
#include <cassert>
#include <spdlog/spdlog.h>

#include "display.h"
#include "sprite.h"
#include "errors.h"

int main() {
    spdlog::info("OK, now we are on.");
    try {
        Display disp("Nice");
        bool running = true;
        SDL_Event e;
        auto sprite = new Sprite(
            "res/1.png",
            SDL_Rect{0, 0, 100, 100}
            );
        auto sprite2 = new Sprite(
            "res/1.png",
            SDL_Rect{100, 100, 100, 100}
            );
        disp.add_sprite(sprite);
        disp.add_sprite(sprite2);
        while (running) {
            disp.draw();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }
            }
        }
        spdlog::warn("Gone.");
    } catch (const SDLError& err) {
        return 1;
    }
    sol::state lua;
    int x = 0;
    lua.set_function("beep", [&x] { ++x; });
    lua.script("beep()");
    assert(x == 1);
    return 0;
}
