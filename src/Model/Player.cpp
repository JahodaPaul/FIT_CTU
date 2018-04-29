//
// Created by pjahoda on 29.4.18.
//

#include <Model/Player.h>

namespace RG{


    Player::Player() {
        player = sf::RectangleShape(sf::Vector2f(91.0f,91.0f));
//        playerTexture.loadFromFile();
//        player.setTexture(&playerTexture);
        animation = std::make_shared<Animation>("../assets/graphics/objects/characters/player.png", 91, 91, 12, 1.0f);
    }

    void Player::SetPosition(float x, float y) {
        this->x = x;
        this->y = y;
//        player.setPosition(x,y);
        animation->setPosition(sf::Vector2f(this->x,this->y));
    }

    std::pair<float, float> Player::GetPosition() {
        return std::make_pair(x,y);
    }

    sf::RectangleShape Player::GetPlayerRectangleShape() {
        return player;
    }

    std::shared_ptr<Animation> Player::GetAnimation() {
        return this->animation;
    }

    void Player::Update() {
        this->animation->update(1.0f);
    }
}