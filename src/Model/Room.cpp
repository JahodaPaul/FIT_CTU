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
  }
}
