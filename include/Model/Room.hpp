#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Model/Entity.hpp"
#include "Model/Object.hpp"

namespace RG {
  namespace Model {

    /**
     * \class Room
     * \brief This class desribes a room. There can be objects and entities inside
     * a room. The player can get to a different room using either doors or
     * stairs.
     */
    class Room : public Object {
      public:
        /// constructor
        Room(unsigned int x, unsigned int y);

        /// destructor
        ~Room();

        void SetDoors(std::vector<bool> doors);

        void AddDoors(unsigned int num, bool add = true);

        void RemoveDoors(unsigned int num);

        std::vector<bool> GetDoors(void) const;

        void AddWalls(float screen_w, float screen_h, float door_w, float wall_w,
            float wall_h);

        void Move(b2Vec2 PlayerPos);

        void AddEnemy(b2Body* body);

        void RecvAttack(int enemy_attack, std::shared_ptr<b2World> world);

        std::vector<std::shared_ptr<RG::Model::Entity>> GetEntities(void) const;
   
        void SweepDeadEntities(void);

      private:
        /// position in the map grid
        std::pair<unsigned int, unsigned int> m_GridPosition;

        /// all entities inside the room
        std::vector<std::shared_ptr<RG::Model::Entity>> m_Entities;

        /// whether the room has been visited by the player or not
        bool m_Visited;

        /// doors leading to another rooms -- whether there are doors on the
        // western, northern, eastern or southern walls
        std::vector<bool> m_Doors;
    };
  }
}
