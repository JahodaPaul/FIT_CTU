#pragma once

#include <string>
#include <vector>

#include "Model/Entity.hpp"
#include "Model/Room.hpp"

#include "common.hpp"

namespace RG {
  namespace Model {
    class Player : public Entity {
      public:
        Player(std::string name);

        void ChangeFloor(unsigned int floor_idx);

        void ChangeRoom(std::shared_ptr<RG::Model::Room> room);

        std::vector<b2Body*> m_Bodies;

        std::shared_ptr<RG::Model::Object> Shoot(
            const b2Vec2& target, std::shared_ptr<b2World> world);

      private:
        std::shared_ptr<RG::Model::Room> m_Room;
    };
  }
}
