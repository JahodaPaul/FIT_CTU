#include "Model/Floor.hpp"

namespace RG {
  namespace Model {
    Floor::Floor(unsigned int level, unsigned int rooms, unsigned int pos_X,
        unsigned int pos_Y)
      : m_Level(level)
        , m_X(pos_X)
        , m_Y(pos_Y)
        , m_RoomHeight(100)
        , m_RoomWidth(100)
    {
      m_World = std::make_shared<b2World>(b2Vec2{ 0.0f, 0.0f });

      for (unsigned int i = 0; i < rooms; ++i) {
        RG::Model::Room* tmp_room = new RG::Model::Room(i, 0);
        b2BodyDef* room_bodyDef = new b2BodyDef;
        room_bodyDef->type = b2_dynamicBody;
        room_bodyDef->position.Set(i * m_RoomHeight, 0 * m_RoomWidth);
        tmp_room->m_Body = m_World->CreateBody(room_bodyDef);

        m_Rooms.insert({ i, { { 0, tmp_room } } });
      }
    }

    Floor::~Floor() {}

    unsigned int Floor::GetLevel(void) const { return m_Level; }

    const RG::Model::Room& Floor::GetRoom(void) const
    {
      auto it_row = m_Rooms.find(m_X);
      auto it_col = it_row->second.find(m_Y);
      return *(it_col->second);
    }

    b2Body* Floor::GetPlayerBody(b2BodyDef* bodyDef)
    {
      return m_World->CreateBody(bodyDef);
    }

    void Floor::Step(float time_step) {
      this->m_World->Step(time_step, 8,3);
      this->m_World->ClearForces();
    }
  }
}
