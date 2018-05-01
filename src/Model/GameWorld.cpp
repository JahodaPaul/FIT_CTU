#include "Model/GameWorld.hpp"

namespace RG{
  namespace Model{
    GameWorld::GameWorld(std::string title) : m_Title(title), m_World({0.0f, 0.0f}),
      m_Player(RG::Model::Player(0,0,std::make_shared<b2World>(m_World),"Hrac")), m_CurrentFloorIdx(0),
      m_Floors({RG::Model::Floor(0, 2)}) {
      }

    GameWorld::~GameWorld(){}

    std::string GameWorld::GetTitle ( void ) const {
      return m_Title;
    }

   // RG::Model::Room* GameWorld::GetCurrentRoom ( void ) {
      //return &(m_Floors[m_CurrentFloorIdx]);
   // }

    const RG::Model::Player& GameWorld::GetPlayer ( void ) const {
      return m_Player;
    }
  }
}
