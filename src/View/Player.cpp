//
// Created by pjahoda on 29.4.18.
//

#include "View/Player.hpp"
#include "View/View.hpp"
#include "Util/Observer.hpp"
#include "Model/Floor.hpp"

namespace RG{
    namespace View {
        Player::Player(GameScene * gameScene) :
            Entity( gameScene )
            ,relativeMoveX( 0 )
            ,relativeMoveY( 0 )
            {
            }

        Player::~Player() {}

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
