#pragma once

#include <map>
#include <string>

#include "Model/Object.hpp"
#include "Model/Room.hpp"

namespace RG {
  namespace Model {
    /**
     * \class Floor
     * \brief This class desribes a floor inside the game world. There are
     * multiple rooms inside and the transition between floors is by stairs.
     */
    class Floor {
      public:
        /// constructor
        Floor(unsigned int level, unsigned int rooms, unsigned int pos_X,
            unsigned int pos_Y);

        /// destructor
        ~Floor();

        /// returns how many floors under ground this floor is
        unsigned int GetLevel(void) const;

        const RG::Model::Room& GetRoom(void) const;

        b2Body* GetPlayerBody(b2BodyDef* bodyDef);
        
        void Step(float time_step);

      private:
        /// array of rooms present at this floor
        std::map<unsigned int, std::map<unsigned int, RG::Model::Room*>> m_Rooms;

        /// how deep under ground the floor is
        unsigned int m_Level;

        /// title of the floor
        std::string m_Title;

        /// box2d world, where all objects will be placed
        std::shared_ptr<b2World> m_World;

        unsigned int m_X;
        unsigned int m_Y;

        unsigned int m_RoomHeight;
        unsigned int m_RoomWidth;
    };
  }
}
