#include "Model/Model.hpp"

namespace RG {
  namespace Model {
    Model::Model()
      : m_CurrentFloorIdx(0)
    {
      RG::Model::Floor* tmp_floor = new RG::Model::Floor(0, 2, 0, 0);
      m_Floors.push_back(tmp_floor); // FIXME(vanda, replace by world generation)

      // adding the player
      b2BodyDef bodyDef;
      bodyDef.type = b2_dynamicBody;
      bodyDef.position.Set(300, 300);
      m_Player = std::make_shared<RG::Model::Entity>("Hrac", 100);
      m_Player->m_Body = m_Floors[m_CurrentFloorIdx]->GetPlayerBody(&bodyDef);
      b2CircleShape circle;
      circle.m_p.Set(0, 0);
      circle.m_radius = 35;
      m_PlayerRadius = 35;
      m_Player->AddShape(&circle, 0.01f, BIT_PLAYER, BIT_ENEMY | BIT_WALL);
    }

    Model::~Model() {
      for(auto i:m_Floors) delete i;
    }

    void Model::Move(float x, float y)
    {
      m_Player->Move(b2Vec2(x, y));
      m_Floors[m_CurrentFloorIdx]->UpdateID(m_Player->GetPosition());
    }

    const RG::Model::Room& Model::GetCurrentRoom(void) const
    {
      return m_Floors[m_CurrentFloorIdx]->GetRoom();
    }

    std::pair<float, float> Model::GetPlayerPosition(void) const
    {
      float _x = m_Player->GetPosition().x
        - m_Floors[m_CurrentFloorIdx]->m_X
        * m_Floors[m_CurrentFloorIdx]->m_RoomWidth;

      float _y = m_Player->GetPosition().y
        - m_Floors[m_CurrentFloorIdx]->m_Y
        * m_Floors[m_CurrentFloorIdx]->m_RoomHeight;

      return std::pair<float, float>{ _x, _y };
    }

    float Model::GetPlayerRotation(void) const
    {
      return m_Player->GetAngle() * 180 / M_PI;
    }

    float Model::GetPlayerRadius(void) const { return m_PlayerRadius; }

    unsigned int Model::GetRoomId(void) const
    {
      unsigned int _x = m_Floors[m_CurrentFloorIdx]->m_X;
      unsigned int _y = m_Floors[m_CurrentFloorIdx]->m_Y;
      return 1000000 * m_CurrentFloorIdx + 1000 * _x + _y;
    }

    int Model::GetFloorLevel(void) const { return m_CurrentFloorIdx; }

    std::vector<bool> Model::GetRoomDoors(int floorID) const
    {
      std::vector<bool> tmp = GetCurrentRoom().GetDoors();
      tmp.resize(4);
      return tmp;
    }

    void Model::Step(float time_step)
    {
      this->m_Floors[this->m_CurrentFloorIdx]->Step(
          time_step, m_Player->GetPosition());
    }
  }
}
