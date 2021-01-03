#define SDL_MAIN_HANDLED

#include <sol/sol.hpp>
#include <cassert>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "display.h"
#include "sprite.h"
#include "errors.h"
#include "pool.h"
#include "game.h"

using json = nlohmann::json;

int main() {
    spdlog::set_level(spdlog::level::level_enum::debug);
    spdlog::info("OK, now we are on.");
    auto g = Game();
    g.run();
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
