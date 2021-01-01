#include "game.h"
#include "errors.h"

#include <SDL.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <spdlog/spdlog.h>

using json = nlohmann::json;

Game::Game() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDLError();
    std::ifstream config_file{"config/user/default.json"};
    std::string cfg_str{
        std::istreambuf_iterator<char>(config_file),
        std::istreambuf_iterator<char>()
    };
    spdlog::info(cfg_str);
    auto config = json::parse(cfg_str);
    spdlog::info(config["fullscreen"]);
    // m_windows_.push_back(new Display("Perfect Delivery",config[""]));
}
