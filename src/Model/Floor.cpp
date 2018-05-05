#include "Model/Floor.hpp"

namespace RG {
  namespace Model {
    Floor::Floor(unsigned int level, unsigned int rooms)
      : m_Level(level)
    {
      m_World = std::make_shared<b2World>(b2Vec2{ 0.0f, 0.0f });
      b2BodyDef bodyDef;
      bodyDef.type = b2_dynamicBody;
      bodyDef.position.Set(0, 0);
      for (unsigned int i = 0; i < rooms; ++i) {
        m_Rooms.insert({ i, { { 0, Room(i, 0) } } });
      }
    }

    Floor::~Floor() {}

    unsigned int Floor::GetLevel(void) const { return m_Level; }
    
    const RG::Model::Room& Floor::GetRoom(void) const {
      auto it_row = m_Rooms.find(m_X);
      auto it_col = it_row->second.find(m_Y);
      return it_col->second;
    }
  }
}
