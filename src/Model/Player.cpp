<<<<<<< HEAD
#include <Model/Player.hpp>

namespace RG {
  namespace Model {
    Player::Player(float x, float y, std::shared_ptr<b2World> world, std::string name) :
        Entity(x, y, world, name) {
    }
    
    Player::~Player(){
    }

    void Player::Move ( void ) {} // FIXME (vanda)
  }
}
=======
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
>>>>>>> develop
