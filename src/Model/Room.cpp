#include "Model/Room.hpp"

namespace RG {
  namespace Model {
    Room::Room(unsigned int x, unsigned int y)
      : Object("Room")
        , m_GridPosition({ x, y })
        , m_Visited(false)
        {
        }

    Room::~Room() {}

    void Room::SetDoors(std::vector<bool> doors) { m_Doors = doors; }

    void Room::AddWalls(
        float screen_w, float screen_h, float door_w, float wall_w, float wall_h)
    {
      float hw1 = (screen_w - door_w) / 4;
      float hh1 = wall_h / 2;

      float ow1 = screen_w - 2 * hw1;
      float oh1 = screen_h - 2 * hh1;

      float hh2 = (screen_h - door_w) / 4;
      float hw2 = wall_w / 2;

      float ow2 = screen_w - 2 * hw2;
      float oh2 = screen_h - 2 * hh2;

      float wall_density = 1000;

      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          b2PolygonShape* dynBox = new b2PolygonShape;
          dynBox->SetAsBox(hw1, hh1,
              { m_Body->GetPosition().x + hw1 + i * ow1,
              m_Body->GetPosition().y + hh1 + j * oh1 },
              0);
          this->AddShape(dynBox, wall_density);
        }
      }

      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          b2PolygonShape* dynBox = new b2PolygonShape;
          dynBox->SetAsBox(hw2, hh2,
              { m_Body->GetPosition().x + hw2 + i * ow2,
              m_Body->GetPosition().y + hh2 + j * oh2 },
              0);
          this->AddShape(dynBox, wall_density);
        }
      }

      for (unsigned int i = 0; i < m_Doors.size(); ++i) {
        if (m_Doors[i])
          continue;
        b2PolygonShape* dynBox = new b2PolygonShape;
        if (i % 2 == 0) {
          unsigned int cnt = i / 2;
          dynBox->SetAsBox(door_w / 2, wall_h / 2,
              { m_Body->GetPosition().x + screen_w / 2,
              m_Body->GetPosition().y + wall_h / 2 + cnt * oh1 },
              0);
        } else {
          unsigned int cnt = 1 - (i / 2);
          dynBox->SetAsBox(wall_w / 2, door_w / 2,
              { m_Body->GetPosition().x + wall_w / 2 + cnt * ow2,
              m_Body->GetPosition().y + screen_h / 2 },
              0);
        }
        this->AddShape(dynBox, wall_density);
      }
    }
  }
}
