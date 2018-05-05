#pragma once

#include <utility> // std::pair
#include <vector>  // std::vector

#include "Model/Floor.hpp"  // RG::Model::Floor
#include "Model/Player.hpp" // RG::Model::Player
#include "Model/Room.hpp"   // RG::Model::Room

namespace RG {
  namespace Model {
    /**
     * \class Model
     * \brief this class wraps up all the logic in the game and provides an
     * interface for other layers - View and Controller
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
        const RG::Model::Room& GetCurrentRoom(void) const;

        /// returns player's current position
        std::pair<float, float> GetPlayerPosition(void) const; // TODO

        /// returns player's current rotation in degrees // FIXME(vanda, units)
        float GetPlayerRotation(void) const;

        /// returns player's radius
        float GetPlayerRadius(void) const;

        /// returns how deep under ground the player currently is
        int GetFloorLevel(void) const;

        /// returns a unique room identifier
        int GetRoomId(void) const;

        std::vector<bool> GetRoomDoors(int) const;

        // std::vector<type> GetEntityList(void) const;
      private:
        void GenerateFloors(unsigned int seed);

        /// current game world
        RG::Model::GameWorld m_GameWorld;

        /// an instance of the Player
        std::shared_ptr<RG::Model::Player> m_Player;

        unsigned int m_CurrentFloorIdx;

        std::vector<RG::Model::Floor> m_Floors;
    };
  }
}
