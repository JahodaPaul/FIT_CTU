#include "Model/DynamicObject.hpp"

namespace RG {
  namespace Model {
    DynamicObject::DynamicObject(b2BodyDef* body, std::string name)
      : Object(body, name)
    {
    }

    DynamicObject::~DynamicObject() {}

    void DynamicObject::Move(const b2Vec2& v)
    {
      m_Body->ApplyForce(v, m_Body->GetPosition(),
          true); // FIXME (vanda, linearimpulse, add damping?)
    }
  }
}
