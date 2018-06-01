#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Model/Entity.hpp"
#include "Model/Object.hpp"
#include "Model/Stairs.hpp"
#include "Util/Observer.hpp"

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
        /**
         * \function Room
         * \brief constructor
         * @param x horizontal position in the rooms grid
         * @param y vertical position in the rooms grid
         */
        Room(unsigned int x, unsigned int y);

        /**
         * \function ~Room
         * \brief destructor
         */
        ~Room();

        /**
         * \function SetDoors
         * \brief changes where doors are and where there are not, does not make
         * physical changes unless called before AddWalls
         */
        void SetDoors(std::vector<bool> doors);

        /**
         * \function AddDoors
         * \brief adds or removes doors, does not make physical changes unless
         * called before AddWalls
         */
        void AddDoors(unsigned int num, bool add = true);

        /**
         * \function RemoveDoors
         * \brief removes doors, does not make physical changes unless called before
         * AddWalls
         */
        void RemoveDoors(unsigned int num);

        /**
         * \function GetDoors
         * \brief returns where the doors are (order: top, left, down, right)
         */
        std::vector<bool> GetDoors(void) const;

        /**
         * \function AddWalls
         * \brief adds physical walls and doors
         * @param screen_w width of the screen
         * @param screen_h height of the screen
         * @param door_w width of doors
         * @param wall_w width of walls(on left and right side)
         * @param wall_h width of walls(on top and bottom)
         */
        void AddWalls(float screen_w, float screen_h, float door_w, float wall_w,
            float wall_h);

        /**
         * \function Move
         * \brief moves all entities in the room
         * @param PlayerPos player's current position(entities follow him)
         */
        void Move(b2Vec2 PlayerPos);

        /**
         * \function AddEnemy
         * \brief adds an enemy to the room
         * @param body done Box2D body to just assign to an enemy
         */
        void AddEnemy(b2Body* body);

        /**
         * \function RecvAttack
         * \brief manages what happens when something collides with walls
         * @param enemy_attack how strong the enemy is
         */
        void RecvAttack(int enemy_attack);

        /**
         * \function GetEntities
         * \brief returns all entities in the room
         */
        std::vector<std::shared_ptr<RG::Model::Entity>> GetEntities(void) const;

        /**
         * \function SweepDeadEntities
         * \brief checks whether entities are alive or dead and clears them if they
         * are dead
         */
        void SweepDeadEntities(void);

        /**
         * \function AddStairs
         * \brief adds stairs to the room
         * @param up whether the stairs lead up or not
         */
        void AddStairs(bool up, std::shared_ptr<b2World> world,
            unsigned int RoomWidth, unsigned int RoomHeight);

        /**
         * \function AddStairsObserver
         * \brief Adds an observer to all stairs in the room
         */
        void AddStairsObserver(RG::Util::Observer* obs);

        /**
         * \function GetStairs
         * \brief returns all stairs in the room
         * @return vector of shared pointers, size=2, result[0] = stairs down,
         * result[1] = stairs up, filled with nullptr if stairs are not present
         */
        std::vector<std::shared_ptr<RG::Model::Stairs>> GetStairs(void) const;

      private:
        /// position in the map grid
        std::pair<unsigned int, unsigned int> m_GridPosition;

        /// all entities inside the room
        std::vector<std::shared_ptr<RG::Model::Entity>> m_Entities;

        /// whether the room has been visited by the player or not
        bool m_Visited;

        /// doors leading to another rooms -- whether there are doors on the
        /// top, left, down, right walls
        std::vector<bool> m_Doors;

        std::vector<std::shared_ptr<RG::Model::Stairs>> m_Stairs;
    };
  }
}
