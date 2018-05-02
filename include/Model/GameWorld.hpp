#pragma once

#include <string>
#include <vector>

#include "Model/Floor.hpp"
#include "Model/Player.hpp"
#include "Model/Room.hpp"

namespace RG {
  namespace Model {
    /**
     * \class GameWorld
     * \brief This class holds and maintains information about the world, all floors, objects and entities inside.
     */
    class GameWorld {
      public:
        /// constructor
        GameWorld(std::string title);

        /// destructor
        ~GameWorld();

        /// returns the title of the game world
        std::string GetTitle ( void ) const;

        /// returns a refference to the current room
        //RG::Model::Room* GetCurrentRoom ( void );

        const RG::Model::Player& GetPlayer ( void ) const;

      private:
        /// title of the game world
        std::string m_Title;
      
        /// box2d world, where all objects will be placed
        std::shared_ptr<b2World> m_World;

        /// an instance of the Player
        std::shared_ptr<RG::Model::Player> m_Player;

        unsigned int m_CurrentFloorIdx;

        std::vector<RG::Model::Floor> m_Floors;
    };
  }
}
