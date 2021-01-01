﻿#define SDL_MAIN_HANDLED

#include <sol/sol.hpp>
#include <cassert>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "display.h"
#include "sprite.h"
#include "errors.h"
#include "pool.h"

using json = nlohmann::json;

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
        auto a = Pool<Sprite*>();
        a.add("123", sprite);
        a.add("???", sprite2);
        spdlog::info(a.size());
        spdlog::info(a.is_full());
        while (running) {
            disp.draw();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    running = false;
                }
            }
        }
        spdlog::warn("Gone.");
    } catch (const SDLError&) {
        return 1;
    }
    sol::state lua;
    int x = 0;
    lua.set_function("beep", [&x] { ++x; });
    lua.script("beep()");
    assert(x == 1);
    json j;
    j["nice"] = "work";
    j["good"] = "job";
    spdlog::info(j.dump());
    return 0;
}
