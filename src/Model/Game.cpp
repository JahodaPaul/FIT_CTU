//
// Created by pjahoda on 29.4.18.
//
#include <Model/Game.h>

namespace RG {
    RG::Game::Game() {
        SetPlayer();
    }

    void RG::Game::SetPlayer() {
        player = std::make_shared<Player>();
    }

    std::shared_ptr<Player> RG::Game::GetPlayer() {
        return player;
    }


}
