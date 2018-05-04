//
// Created by pjahoda on 29.4.18.
//

#include "View/Player.hpp"
#include <iostream>

namespace RG{
    namespace View {


        Player::Player() {
            clock = sf::Clock();
            player = sf::RectangleShape(sf::Vector2f(91.0f, 91.0f));
//        playerTexture.loadFromFile();
//        player.setTexture(&playerTexture);
            animation = std::make_shared<Animation>("../assets/graphics/objects/characters/player.png", 91, 91, 12,
                                                    40.0f);
//            this->x = 500;
//            this->y = 500;
            this->time = 0;
            animation->setPosition(sf::Vector2f(this->x, this->y));
        }

        void Player::UpdatePosition(float x, float y) {
            if (x != 0 && y != 0) {
                x /= sqrt(2);
                y /= sqrt(2);
            }
            this->x = this->x + x;
            this->y = this->y + y;
            animation->setRotation(this->GetAngle(x, y));
            animation->setPosition(sf::Vector2f(this->x, this->y));
        }

        void Player::SetPosition(float x, float y) {
            this->x = x;
            this->y = y;
            animation->setPosition(sf::Vector2f(this->x, this->y));
        }

        std::pair<float, float> Player::GetPosition() {
            return std::make_pair(x, y);
        }

        sf::RectangleShape Player::GetPlayerRectangleShape() {
            return player;
        }

        std::shared_ptr<Animation> Player::GetAnimation() {
            return this->animation;
        }

        void Player::Update(float time) {
            if (time != 0) {
                this->time = time;
            }
            this->animation->update(this->clock.getElapsedTime().asMilliseconds());
        }

        void Player::UpdatePlayer(float x, float y) {
            if (x || y) {
                this->UpdatePosition(x, y);
                this->Update(time);
            }
        }

        float Player::GetAngle(float moveX, float moveY) {
            float angle = 0;
            if (moveY > 0 || moveY < 0) {
                if (moveY < 0) {
                    angle = 0;
                } else {
                    angle = 180;
                }

                if (moveX > 0) {
                    float tmp = 1;
                    if (angle == 180) {
                        tmp = -1;
                    }
                    angle += 45 * tmp;
                } else if (moveX < 0) {
                    float tmp = 1;
                    if (angle == 180) {
                        tmp = -1;
                    }
                    angle -= 45 * tmp;
                }
                if (angle < 0) { angle += 360.0; }
                if (angle > 360) { angle -= 360.0; }
            } else {
                if (moveX > 0) {
                    angle = 90;
                } else if (moveX < 0) {
                    angle = 270;
                }
            }
            return angle;
        }

        void Player::DrawPlayer(sf::RenderTarget &target) {
            this->animation->draw(target, sf::RenderStates());
        }
    }
}