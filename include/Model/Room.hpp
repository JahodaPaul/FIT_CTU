#pragma once

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

        void AddWalls(float screen_w, float screen_h, float door_w, float wall_w,
            float wall_h);

      private:
        /// position in the map grid
        std::pair<unsigned int, unsigned int> m_GridPosition;

        /// all entities inside the room
        std::vector<RG::Model::Entity> m_Entities;

        /// whether the room has been visited by the player or not
        bool m_Visited;

        /// doors leading to another rooms -- whether there are doors on the
        // western, northern, eastern or southern walls
        std::vector<bool> m_Doors;
    };
  }
}
