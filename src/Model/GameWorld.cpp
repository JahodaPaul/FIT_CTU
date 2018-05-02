#include "Model/GameWorld.hpp"

namespace RG{
  namespace Model{
    GameWorld::GameWorld(std::string title) : m_Title(title),
       m_CurrentFloorIdx(0),
      m_Floors({RG::Model::Floor(0, 2)}) {
        m_World = std::make_shared<b2World>(b2Vec2{0.0f, 0.0f});
        m_Player = std::make_shared<RG::Model::Player>(0,0,m_World,"Hrac");
      }

    GameWorld::~GameWorld(){}

    std::string GameWorld::GetTitle ( void ) const {
      return m_Title;
    }

   // RG::Model::Room* GameWorld::GetCurrentRoom ( void ) {
      //return &(m_Floors[m_CurrentFloorIdx]);
   // }

    const RG::Model::Player& GameWorld::GetPlayer ( void ) const {
      return *m_Player;
    }
  }
}
