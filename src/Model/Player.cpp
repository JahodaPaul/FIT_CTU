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
