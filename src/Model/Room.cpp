#include "Model/Room.hpp"

namespace RG {
  namespace Model {
    Room::Room(unsigned int x, unsigned int y)
      : Object(NULL, "Room"),
      m_GridPosition({ x, y })
      , m_Visited(false)
      {
        m_BodyDef = new b2BodyDef;
        //m_BodyDef->type
      }

    Room::~Room() {}
  }
}
