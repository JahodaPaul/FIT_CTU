#pragma once

#include <Box2D/Box2D.h> // b2Body, b2World, b2Vec2
#include <utility>       // std::pair
#include <vector>        // std::vector

#include "Model/Entity.hpp" // RG::Model::Player
#include "Model/Floor.hpp"  // RG::Model::Floor
#include "Model/Object.hpp"
#include "Model/Room.hpp" // RG::Model::Room
#include "common.hpp"

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
        void Move(float x, float y);

        /// returns reference to the current room
        const RG::Model::Room& GetCurrentRoom(void) const;

        /// returns reference to the current floor
        RG::Model::Floor& GetCurrentFloor(void) const;

        /// returns player's current position
        std::pair<float, float> GetPlayerPosition(void) const; // TODO

        /// returns player's current rotation in degrees // FIXME(vanda, units)
        float GetPlayerRotation(void) const;

        /// returns player's radius
        float GetPlayerRadius(void) const;

        /// returns how deep under ground the player currently is
        int GetFloorLevel(void) const;

        /// returns a unique room identifier
        unsigned int GetRoomId(void) const;

        std::vector<bool> GetRoomDoors(int) const;

        // std::vector<type> GetEntityList(void) const;

        /**
         * \function Step
         * \brief advance time in the game world
         * @param time_step how much time has passed since the last update
         */
        void Step(float time_step);

        RG::Model::Entity& GetPlayer();

      private:
        void GenerateFloors(unsigned int seed);

        /// the Player
        std::shared_ptr<RG::Model::Entity> m_Player;

        unsigned int m_CurrentFloorIdx;

        std::vector<RG::Model::Floor*> m_Floors;

        float m_PlayerRadius;
    };
  }
}
