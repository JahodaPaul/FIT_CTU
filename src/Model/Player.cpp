//
// Created by pjahoda on 29.4.18.
//

#include <Model/Player.h>

namespace RG{


    Player::Player() {
        player = sf::RectangleShape(sf::Vector2f(100.0f,100.0f));
        sf::Texture playerTexture;
        playerTexture.loadFromFile("../assets/graphics/objects/characters/player.png");
        player.setTexture(&playerTexture);
    }

    void Player::SetPosition(float x, float y) {
        this->x = x;
        this->y = y;
        player.setPosition(x,y);
    }

    std::pair<float, float> Player::GetPosition() {
        return std::make_pair(x,y);
    }

    sf::RectangleShape Player::GetPlayerRectangleShape() {
        return player;
    }
}