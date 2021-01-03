#include "game.h"
#include "errors.h"
#include "util.h"

#include <SDL.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <spdlog/spdlog.h>
#include <vector>
#include <filesystem>

using json = nlohmann::json;
namespace fs = std::filesystem;

Game::Game() { initialize(); }

Game::~Game() { exit(); }

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDLError();
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags)) throw SDLError();

    std::string conf_save_path{"config/user/default.json"};
    if (!fs::exists(fs::path(conf_save_path))) {
        generate_config();
    }
    auto cfg_str = read_all(conf_save_path);
    auto config = json::parse(cfg_str);
    bool fullscreen = config["fullscreen"].get<bool>();
    int width, height;
    for (auto const& k : config["screen"]) {
        if (k["activated"].get<bool>()) {
            width = k["width"];
            height = k["height"];
        }
    }
    spdlog::info("Configuration loaded, screen {0}x{1}", width, height);
    m_display_ = new Display(NAME, width, height, fullscreen);
    m_running_ = true;
    return true;
}

void Game::generate_config() {
    fs::path src("config/default.json");
    fs::path dst("config/user/default.json");
    fs::copy_file(src, dst);
}

void Game::run() {
    auto sprite = new Sprite("res/1.png", SDL_Rect{0, 0, 100, 100});
    auto sprite2 = new Sprite("res/1.png", SDL_Rect{100, 100, 100, 100});
    m_display_->add_sprite(sprite);
    m_display_->add_sprite(sprite2);
    auto a = Pool<Sprite*>();
    a.add("123", sprite);
    a.add("???", sprite2);
    spdlog::info("Pool status: {0}, full={1}", a.size(), a.is_full());
    while (m_running_) {
        loop();
    }
}

void Game::loop() {
    m_display_->draw();
    while (SDL_PollEvent(&m_current_event_) != 0) {
        if (m_current_event_.type == SDL_QUIT) {
            m_running_ = false;
        }
    }
}

void Game::exit() { delete m_display_; }
