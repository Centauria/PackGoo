#pragma once
#include <vector>

#include "display.h"

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
    std::vector<int*> m_windows_;
    volatile bool m_running_;
};
