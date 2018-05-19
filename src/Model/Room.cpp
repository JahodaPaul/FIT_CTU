#include "Model/Room.hpp"

namespace RG {
  namespace Model {
    Room::Room(unsigned int x, unsigned int y)
      : Entity("Room", 0)
        , m_GridPosition({ x, y })
        , m_Visited(false)
        {
        }

    Room::~Room() {}

    void Room::SetDoors(std::vector<bool> doors) { m_Doors = doors; }

    std::vector<bool> Room::GetDoors(void) const { return m_Doors; }

    void Room::AddWalls(
        float screen_w, float screen_h, float door_w, float wall_w, float wall_h)
    {
      float hw1 = (screen_w - door_w) / 4 - wall_w / 2;
      float hh1 = 10;

      float ow1 = 2 * hw1 + door_w;
      float oh1 = screen_h - 2 * wall_h + hh1;

      float hh2 = (screen_h - door_w) / 4 - wall_h / 2;
      float hw2 = 10;

      float ow2 = screen_w - 2 * wall_w + 2 * hw2;
      float oh2 = door_w + 2 * hh2;

      float wall_density = 1000000;

      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          b2PolygonShape* dynBox = new b2PolygonShape;
          dynBox->SetAsBox(
              hw1, hh1, { wall_w + hw1 + i * ow1, (wall_h - hh1) + j * oh1 }, 0);
          this->AddShape(dynBox, wall_density, BIT_WALL, BIT_PLAYER | BIT_ENEMY);
        }
      }

      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          b2PolygonShape* dynBox = new b2PolygonShape;
          dynBox->SetAsBox(
              hw2, hh2, { (wall_w - hw2) + i * ow2, wall_h + hh2 + j * oh2 }, 0);
          this->AddShape(dynBox, wall_density, BIT_WALL, BIT_PLAYER | BIT_ENEMY);
        }
      }

      for (unsigned int i = 0; i < m_Doors.size(); ++i) {
        if (m_Doors[i])
          continue;
        b2PolygonShape* dynBox = new b2PolygonShape;
        if (i % 2 == 0) {
          unsigned int cnt = i / 2;
          dynBox->SetAsBox(
              door_w / 2, hh1, { screen_w / 2, wall_h - hh1 + cnt * oh1 }, 0);
        } else {
          unsigned int cnt = 1 - (i / 2);
          dynBox->SetAsBox(
              hw2, door_w / 2, { wall_w - hw2 + cnt * ow2, screen_h / 2 }, 0);
        }
        this->AddShape(dynBox, wall_density, BIT_WALL, BIT_PLAYER | BIT_ENEMY);
      }
    }

    void Room::Move(b2Vec2 PlayerPos)
    {
      for (auto i : m_Entities) {
        i.Move(b2Vec2{ PlayerPos.x - i.m_Body->GetPosition().x,
            PlayerPos.y - i.m_Body->GetPosition().y });
      }
    }

    void Room::AddEnemy(b2Body* body)
    {
      m_Entities.emplace_back("Enemy");
      m_Entities[m_Entities.size() - 1].m_Body = body;
      b2CircleShape* circle = new b2CircleShape;
      circle->m_p.Set(0, 0);
      circle->m_radius = 35;
      m_Entities[m_Entities.size() - 1].AddShape(
          circle, 0.01f, BIT_ENEMY, BIT_PLAYER | BIT_WALL);
      std::cout << m_Entities.size() << std::endl;
    }
  }
}
