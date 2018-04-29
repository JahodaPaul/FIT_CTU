//
// Created by pjahoda on 29.4.18.
//

#include <Model/Player.hpp>

namespace RG{


    Player::Player() {

    }

    void Player::Move(float x, float y) {
        //TODO
    }

    std::pair<float, float> Player::GetPosition() const {
        return std::make_pair(x,y);;
    }
}