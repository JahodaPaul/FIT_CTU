//
// Created by pjahoda on 29.4.18.
//

#include "View/Player.hpp"
#include "View/View.hpp"

namespace RG{
    namespace View {


        Player::Player() :
        relativeMoveX( 0 ),
        relativeMoveY( 0 ) {
            player = sf::RectangleShape(sf::Vector2f(91.0f, 91.0f));
            animation = std::make_shared<Animation>("/usr/share/RG/assets/graphics/objects/characters/player.png", 91, 91, 12,
                                                    40.0f);
            this->time = 0;
            this->windowX = 0;
            this->windowY = 0;
            animation->setPosition(sf::Vector2f(this->x, this->y));
            animation->goToFrame(0);
            animation->startAnimation();
        }

        void Player::SetPosition(float x, float y) {
            this->x = x;
            this->y = y;
            animation->setPosition(sf::Vector2f(this->x*(windowX/1920), this->y*(windowY/1080)));
        }

        void Player::UpdatePlayer(View * view, float timeElapsed) {
            float absoluteX = view->getGameController()->GetPlayerPos().first;
            float absoluteY = view->getGameController()->GetPlayerPos().second;
            if (absoluteX != this->x || absoluteY != this->y) {
                this->animation->setRotation(view->getGameController()->GetPlayerAngle() + 90.0f);
                this->SetPosition(absoluteX,absoluteY);
                this->animation->update(timeElapsed);
            }
        }

        void Player::DrawPlayer(sf::RenderTarget &target) {
            this->animation->draw(target, sf::RenderStates());
        }

        void Player::SetPlayerScale(float windowWidth, float windowHeight){
            if(windowWidth != windowX || windowHeight != windowY) {
                float scaleX = (windowWidth / 20) / this->animation->getSize().x;
                float scaleY = (windowWidth / 20) / this->animation->getSize().x;
                this->animation->setScale(scaleX, scaleY);
                windowX = windowWidth;
                windowY = windowHeight;
            }
        }

        void RG::View::Player::SetPlayerSpeedX(float x) {
            this->relativeMoveX += x;
        }

        void RG::View::Player::SetPlayerSpeedY(float y) {
            this->relativeMoveY += y;
        }

        float RG::View::Player::GetPlayerSpeedX() {
            return this->relativeMoveX;
        }

        float RG::View::Player::GetPlayerSpeedY() {
            return this->relativeMoveY;
        }
    }
}
