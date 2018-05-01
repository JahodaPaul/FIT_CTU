#pragma once

#include <utility> // std::pair

#include "Model/GameWorld.hpp"
#include "Model/Room.hpp"

namespace RG {
  namespace Model {
    /**
     * \class Model
     * \brief this class wraps up all the logic in the game and provides an interface for other layers - View and
     * Controller
     */
    class Model {
      public:
        /// constructor
        Model();

        /// destructor
        ~Model();

        /// moves the player
        void Move();

        /// returns reference to the current room
        const RG::Model::Room& GetCurrentRoom ( void ) const;

        /// returns player's current position
        std::pair<float, float> GetPlayerPosition ( void ) const; // TODO 

        /// returns player's current rotation in degrees // FIXME(vanda, units)
        float GetPlayerRotation ( void ) const;

        /// returns player's radius
        float GetPlayerRadius ( void ) const;

//        b2Vec GetPlayerVector ( void ) const;

        int GetFloorLevel ( void ) const;

        int GetRoomId (void) const;

      private:
        /// current game world
        RG::Model::GameWorld m_GameWorld;
    };
  }
}
