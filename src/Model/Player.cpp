//
// Created by pjahoda on 29.4.18.
//

#include <Model/Player.h>
#include <iostream>

namespace RG{


    Player::Player() {
        player = sf::RectangleShape(sf::Vector2f(91.0f,91.0f));
//        playerTexture.loadFromFile();
//        player.setTexture(&playerTexture);
        animation = std::make_shared<Animation>("../assets/graphics/objects/characters/player.png", 91, 91, 12, 0.1f);
        this->x = 500;
        this->y = 500;
        this->time = 0;
        animation->setPosition(sf::Vector2f(this->x,this->y));
    }

    void Player::UpdatePosition(float x, float y) {
        this->x = this->x+x;
        this->y = this->y+y;
        animation->setRotation(this->GetAngle(x,y));
        animation->setPosition(sf::Vector2f(this->x,this->y));
    }

    void Player::SetPosition(float x, float y) {
        this->x = x;
        this->y = y;
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

    void Player::Update(float time) {
        this->time = this->time+time;
        this->animation->update(this->time);
    }

    float Player::GetAngle(float moveX, float moveY) {
        float angle = 0;

        if(moveY>0 || moveY<0){
            if(moveY<0){
                angle = 0;
            }
            else{
                angle = 180;
            }

            if(moveX>0){
                angle+=45;
            }
            else if(moveX<0){
                angle -= 45;
            }
            if(angle < 0){angle += 360.0;}
            if(angle > 360) {angle -= 360.0;}
        }
        else{
            if(moveX>0){
                angle = 90;
            }
            else if(moveX<0){
                angle = 270;
            }
        }
        return angle;
    }
}