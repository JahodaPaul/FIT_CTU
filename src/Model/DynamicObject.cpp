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
      //      m_Body->ApplyAngularImpulse(M_PI, true);
      if (v.y != 0) {
        double angle = std::atan(v.x / v.y);
        if (v.x != 0)
          angle += M_PI / 2;
        m_Body->SetTransform(m_Body->GetPosition(), angle);
      } else {
        m_Body->SetTransform(
            m_Body->GetPosition(), v.x > 0 ? M_PI / 2 : M_PI * 3 / 2);
      }
      m_Body->ApplyForce(v, m_Body->GetWorldCenter(), true);
      m_Body->SetLinearDamping(0.04f);
      m_Body->SetAngularDamping(2.0f);
    }
  }
}
