#include "Model/DynamicObject.hpp"

namespace RG {
  namespace Model {
    DynamicObject::DynamicObject(float x, float y, std::shared_ptr<b2World> world, std::string name) : 
      Object(x, y, world, name, true){}

    DynamicObject::~DynamicObject(){}
  }
}
