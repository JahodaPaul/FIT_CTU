#include "Model/Room.hpp"

namespace RG {
  namespace Model {
    Room::Room(unsigned int x, unsigned int y)
      : Object("Room")
        , m_GridPosition({ x, y })
        , m_Visited(false)
        {
          m_Doors.resize(4, false);
          m_Stairs.resize(2, nullptr);
        }

    Room::~Room() {}

    void Room::SetDoors(std::vector<bool> doors) { m_Doors = doors; }

    void Room::AddDoors(unsigned int num, bool add)
    {
      if (num < m_Doors.size())
        m_Doors[num] = add;
    }

    void Room::SweepDeadEntities(void)
    {
      for (unsigned int i = 0; i < m_Entities.size(); ++i) {
        if (m_Entities[i]->Deleted) {
          m_Entities[i] = m_Entities.back();
          m_Entities.pop_back();
        }
      }
    }

    void Room::RemoveDoors(unsigned int num) { AddDoors(num, false); }

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
          b2PolygonShape dynBox;
          dynBox.SetAsBox(
              hw1, hh1, { wall_w + hw1 + i * ow1, (wall_h - hh1) + j * oh1 }, 0);
          this->AddShape(&dynBox, wall_density, BIT_WALL, BIT_PLAYER | BIT_ENEMY);
        }
      }

      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          b2PolygonShape dynBox;
          dynBox.SetAsBox(
              hw2, hh2, { (wall_w - hw2) + i * ow2, wall_h + hh2 + j * oh2 }, 0);
          this->AddShape(&dynBox, wall_density, BIT_WALL, BIT_PLAYER | BIT_ENEMY);
        }
      }

      for (unsigned int i = 0; i < m_Doors.size(); ++i) {
        if (m_Doors[i])
          continue;
        b2PolygonShape dynBox;
        if (i % 2 == 0) {
          unsigned int cnt = i / 2;
          dynBox.SetAsBox(
              door_w / 2, hh1, { screen_w / 2, wall_h - hh1 + cnt * oh1 }, 0);
        } else {
          unsigned int cnt = 1 - (i / 2);
          dynBox.SetAsBox(
              hw2, door_w / 2, { wall_w - hw2 + cnt * ow2, screen_h / 2 }, 0);
        }
        this->AddShape(&dynBox, wall_density, BIT_WALL, BIT_PLAYER | BIT_ENEMY);
      }
    }

    void Room::Move(b2Vec2 PlayerPos)
    {
      for (auto i : m_Entities) {
        i->Move(b2Vec2{ PlayerPos.x - i->m_Body->GetPosition().x,
            PlayerPos.y - i->m_Body->GetPosition().y });
      }
    }

    void Room::AddEnemy(b2Body* body)
    {
      m_Entities.emplace_back(
          std::make_shared<RG::Model::Entity>("Enemy", rand() % 18 + 1));
      m_Entities[m_Entities.size() - 1]->m_Body = body;
      b2CircleShape circle;
      circle.m_p.Set(0, 0);
      circle.m_radius = 35;
      m_Entities[m_Entities.size() - 1]->AddShape(
          &circle, 0.0001f, BIT_ENEMY, BIT_PLAYER | BIT_WALL);
    }

    void Room::RecvAttack(int enemy_attack) {}

    std::vector<std::shared_ptr<RG::Model::Entity>> Room::GetEntities(void) const
    {
      return m_Entities;
    }

    void Room::AddStairs(bool up, std::shared_ptr<b2World> world,
        unsigned int RoomWidth, unsigned int RoomHeight)
    {
      if (m_Stairs.size() < 2)
        m_Stairs.resize(2);
      if (m_Stairs[up] != nullptr)
        return;

      m_Stairs[up] = std::make_shared<Stairs>(up);
      b2BodyDef stairs_bodyDef;
      stairs_bodyDef.type = b2_dynamicBody;
      stairs_bodyDef.position.Set(
          (m_GridPosition.first + 0.3 + 0.1 * up) * RoomWidth,
          (m_GridPosition.second + 0.5) * RoomHeight); // FIXME
      b2Body* stairs_body = world->CreateBody(&stairs_bodyDef);

      m_Stairs[up]->m_Body = stairs_body;

      b2PolygonShape dynBox;
      dynBox.SetAsBox(30, 30, { 0, 0 }, 0);
      m_Stairs[up]->AddShape(&dynBox, 100000, BIT_STAIRS, BIT_PLAYER);
    }

    void Room::AddStairsObserver(RG::Util::Observer* obs)
    {
      for (unsigned int i = 0; i < 2; ++i) {
        if (m_Stairs.size() > i && m_Stairs[i] != nullptr) {
          m_Stairs[i]->AddObserver(obs);
        }
      }
    }

    std::vector<std::shared_ptr<RG::Model::Stairs>> Room::GetStairs(void) const
    {
      return m_Stairs;
    }
  }
}
