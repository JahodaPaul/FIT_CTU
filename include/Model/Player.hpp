#pragma once

#include <string>
#include <utility>

#include <Model/Entity.hpp>

namespace RG {
  namespace Model {
    /**
     * \class Player
     * \brief Object manipulated by user
     */
    class Player : public Entity {
      public:
        Player(float x, float y, std::shared_ptr<b2World> world, std::string name);

        ~Player();

        void Move( void ); // FIXME (vanda)

      private:
    };
  }
}
