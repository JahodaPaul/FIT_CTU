//
// Created by pjahoda on 29.4.18.
//

#include "Model/Player.hpp"

namespace RG {
  namespace Model {
        Player::Player(float x, float y, std::shared_ptr<b2World> world, std::string name) :
            Entity(x, y, world, name) {
        }

        Player::~Player(){
        }

        void Player::Move ( void ) {
            //TODO
        } // FIXME (vanda)

        std::pair<float, float> Player::GetPosition() const {
              return std::make_pair(x,y);;
        }
  }
}

