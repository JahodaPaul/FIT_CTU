#include <Model/Floor.hpp>

namespace RG {
  namespace Model {
    Floor::Floor(unsigned int level, unsigned int rooms):m_Level(level){
      for(int i=0; i<rooms;++i){
        m_Rooms.insert({i,{{0, Room(i,0)}}});  
      }
    }

    Floor::~Floor(){}

    unsigned int Floor::GetLevel ( void ) const {
      return m_Level; 
    }
  }
}
