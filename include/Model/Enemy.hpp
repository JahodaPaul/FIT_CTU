#pragma once

#include <Box2D/Box2D.h> // b2Body, b2Vec2
#include <cstdlib>

#include "Model/Entity.hpp"
#include "Util/Observer.hpp"

namespace RG {
  namespace Model {
    class Enemy : public Entity {
      public:
        Enemy();

        void Move(const b2Vec2& pos);

      private:
    };
  }
}
