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
        /**
         * \function Model
         * \brief constructor
         */
        Model();

        /**
         * \function ~Model
         * \brief destructor
         */
        ~Model();

        /**
         * \function Move
         * \brief moves the player
         * @param x first coordinate of the movment vector
         * @param y second coordinate of the movement vector
         */
        void Move(float x, float y);

        /**
         * \brief returns reference to the current room
         */
        const RG::Model::Room& GetCurrentRoom(void) const;

        /**
         * \function GetCurrentFloor
         * \brief  returns reference to the current floor
         */
        RG::Model::Floor& GetCurrentFloor(void) const;

        /**
         * \function GetFloorLevel
         * \brief  returns how deep under ground the player currently is
         */
        int GetFloorLevel(void) const;

        /**
         * \function GetRoomId
         * \brief  returns a unique room identifier
         */
        unsigned int GetRoomId(void) const;

        std::vector<bool> GetRoomDoors(int) const;

        /**
         * \function Step
         * \brief advance time in the game world
         * @param time_step how much time has passed since the last update
         */
        void Step(float time_step);

        RG::Model::Entity& GetPlayer();

      private:
        /**
         * \function GenerateFloors
         * \brief pseudorandomly generate floors
         * @param seed initiates the random generator
         */
        void GenerateFloors(unsigned int seed);

        /// the Player
        std::shared_ptr<RG::Model::Entity> m_Player;

        unsigned int m_CurrentFloorIdx;

        std::vector<RG::Model::Floor*> m_Floors;

        float m_PlayerRadius;
    };
  }
}
