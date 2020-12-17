#include <sol/sol.hpp>
#include <cassert>
#include <spdlog/spdlog.h>

#include "display.h"
#include "errors.h"

int main() {
    spdlog::info("OK, now we are on.");
    try {
        Display disp("Nice");
        bool running = true;
        SDL_Event e;
        disp.add_image("res/1.png");
        while (running) {
            disp.draw();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }
            }
        }
        spdlog::warn("Gone.");
    } catch (const InitError &err) {
        spdlog::error("Error while initializing SDL: {0}", err.what());
        return 1;
    }
    sol::state lua;
    int x = 0;
    lua.set_function("beep", [&x] { ++x; });
    lua.script("beep()");
    assert(x == 1);
    return 0;
}
