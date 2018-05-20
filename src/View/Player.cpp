//
// Created by pjahoda on 29.4.18.
//

#include "View/Player.hpp"
#include "View/View.hpp"
#include "Util/Observer.hpp"
#include "Model/Floor.hpp"

namespace RG{
    namespace View {
        Player::Player() :
            Observer()
            ,correctionX( 0 )
            ,correctionY( 0 )
            ,m_moved{ false }
            ,relativeMoveX( 0 )
            ,relativeMoveY( 0 )
            {
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

        Player::~Player() {}

        void Player::SetPosition(float x, float y) {
            this->x = x;
            this->y = y;
            animation->setPosition(sf::Vector2f(this->x*(windowX/1920), this->y*(windowY/1080)));
        }

        void Player::UpdatePlayer(View * view, float timeElapsed) {
            if (m_moved) {
                this->animation->update(timeElapsed);
                m_moved = false;
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

        void RG::View::Player::onNotify(const Util::Subject * subject, Util::Event event) {
            switch(event) {
                case Util::Event::ENTITY_MOVE:
                    {
                        Model::Entity * entity = (Model::Entity*)subject;
                        float absoluteX = entity->GetPosition().x - correctionX;
                        float absoluteY = entity->GetPosition().y - correctionY;
                        this->animation->setRotation(entity->GetAngle() * 180 / M_PI + 90);
                        this->SetPosition(absoluteX,absoluteY);
                        m_moved = true;
                        break;
                    }
                case Util::Event::ROOM_CHANGE:
                    {
                        Model::Floor * floor = (Model::Floor*)subject;
                        correctionX = floor->m_X * floor->m_RoomWidth;
                        correctionY = floor->m_Y * floor->m_RoomHeight;
                        break;
                    }
                default:
                    break;
            }       
        }
    }
}
