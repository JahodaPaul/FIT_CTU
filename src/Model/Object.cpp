#include <Model/Object.hpp>

namespace RG {
  namespace Model {
    Object::Object(float x, float y, std::shared_ptr<b2World> world, std::string name, bool dynamic=false):m_World(world), m_Position({x,y}){
      b2BodyDef bodyDef;
      if(dynamic){
        bodyDef.type = b2_dynamicBody;
      } else {
        bodyDef.type = b2_staticBody;
      }
      bodyDef.position.Set(x, y);
      m_Body = m_World->CreateBody(&bodyDef);
    }
    
    Object::~Object(){
      m_World->DestroyBody(m_Body);
    }
    
    std::string Object::GetName ( void ) const {
     return m_Name; 
    }
  }
}
