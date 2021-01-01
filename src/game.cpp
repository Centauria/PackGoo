#include "game.h"
#include "errors.h"
#include "util.h"

#include <SDL.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <spdlog/spdlog.h>
#include <vector>

using json = nlohmann::json;

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDLError();
    auto cfg_str = read_all("config/user/default.json");
    spdlog::info(cfg_str);
    auto config = json::parse(cfg_str);
    auto screen = config["screen"].get<std::vector<int>>();
    spdlog::info("({0}, {1})", screen[0], screen[1]);
    // m_windows_.push_back(new Display("Perfect Delivery",config[""]));
}
