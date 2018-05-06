#include "Model/DynamicObject.hpp"

namespace RG {
  namespace Model {
    DynamicObject::DynamicObject(std::string name)
      : Object(name)
    {
    }

    DynamicObject::~DynamicObject() {}

    void DynamicObject::Move(const b2Vec2& v)
    {
      m_Body->ApplyForce(v, m_Body->GetPosition(), true);
      m_Body->SetLinearDamping(0.05f);
      //m_Body->SetAngularDamping(0.1f);
    }
  }
}
