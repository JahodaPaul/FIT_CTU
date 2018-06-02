#pragma once

#include <Box2D/Box2D.h> // b2Body, b2Vec2
#include <cstdlib>

#include "Model/Entity.hpp"

namespace RG {
  namespace Model {
    class Enemy : public Entity {
      public:
        Enemy();

        void Move(b2Vec2 pos);

      private:
    };
  }
}
