#pragma once

#include <string>
#include <vector>

#include "Model/Entity.hpp"

#include "common.hpp"

namespace RG {
  namespace Model {
    class Player : public Entity {
      public:
        Player(std::string name);

        void ChangeFloor(unsigned int floor_idx);

        std::vector<b2Body*> m_Bodies;

      private:
    };
  }
}
