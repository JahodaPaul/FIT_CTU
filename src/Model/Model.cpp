#include "Model/Model.hpp"

namespace RG {
  namespace Model {
    Model::Model()
      : m_CurrentFloorIdx(0)
    {
      MAX_FLOORS = 5;

      this->GenerateFloors();

      // adding the player
      b2BodyDef bodyDef;
      bodyDef.type = b2_dynamicBody;
      bodyDef.position.Set(300, 300);
      m_Player = std::make_shared<RG::Model::Player>("Hrac");

      b2CircleShape circle;
      circle.m_p.Set(0, 0);
      circle.m_radius = 35;
      m_PlayerRadius = 35;

      m_Player->m_Bodies.resize(MAX_FLOORS);

      for (unsigned int i = 0; i < MAX_FLOORS; ++i) {
        m_Player->m_Bodies[i] = m_Floors[i]->GetPlayerBody(&bodyDef);
        m_Player->AddShape(&circle, 0.01f, BIT_PLAYER,
            BIT_ENEMY | BIT_WALL | BIT_STAIRS, m_Player->m_Bodies[i]);
      }
      m_Player->m_Body = m_Player->m_Bodies[0];
    }

    Model::~Model()
    {
      for (auto i : m_Floors) {
        delete i;
      }
    }

    void Model::Move(float x, float y)
    {
      m_Player->Move(b2Vec2(x, y));
      m_Floors[m_CurrentFloorIdx]->UpdateID(m_Player->GetPosition());
    }

    RG::Model::Floor& Model::GetCurrentFloor(void) const
    {
      return *m_Floors[m_CurrentFloorIdx];
    }

    const RG::Model::Room& Model::GetCurrentRoom(void) const
    {
      return m_Floors[m_CurrentFloorIdx]->GetRoom();
    }

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

    RG::Model::Entity& Model::GetPlayer() { return *m_Player; }

    void Model::onNotify(Util::Subject* subject, Util::Event event)
    {
      switch (event) {
        case Util::Event::FLOOR_UP:
          if (m_CurrentFloorIdx > 0) {
            m_CurrentFloorIdx--;
            m_Player->ChangeFloor(m_CurrentFloorIdx);
            Notify(this, Util::Event::FLOOR_CHANGE);
          }
          break;
        case Util::Event::FLOOR_DOWN:
          if (m_CurrentFloorIdx < MAX_FLOORS - 1) {
            m_CurrentFloorIdx++;
            mainLog.Info("down to" + std::to_string(m_CurrentFloorIdx));
            m_Player->ChangeFloor(m_CurrentFloorIdx);
            Notify(this, Util::Event::FLOOR_CHANGE);
          }
          break;
        default:
          break;
      }
    }

    void Model::GenerateFloors(void)
    {
      for (unsigned int i = 0; i < MAX_FLOORS; ++i) {
        srand(time(NULL));
        RG::Model::Floor* tmp_floor
          = new RG::Model::Floor(i, 10 + rand() % 5, 0, 0, MAX_FLOORS);

        tmp_floor->AddStairsObserver(this, tmp_floor->m_Stairs.first.first,
            tmp_floor->m_Stairs.first.second);
        tmp_floor->AddStairsObserver(this, tmp_floor->m_Stairs.second.first,
            tmp_floor->m_Stairs.second.second);

        m_Floors.push_back(tmp_floor);
      }
    }
  }
}
