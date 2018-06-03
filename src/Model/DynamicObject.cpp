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
      b2Vec2 tmp = v;
      tmp.Normalize();
      tmp *= m_Speed;
      
      float linear_damping = 0.04f;
      float angular_damping = 2.0f;
      if (tmp.y != 0) {
        double angle = std::atan(tmp.x / tmp.y);
        if (angle < 0)
          angle += M_PI;
        else if (angle == 0)
          angle += M_PI / 2;
        if (tmp.y < 0)
          angle += M_PI;
        m_Body->SetTransform(m_Body->GetPosition(), angle);
      } else {
        m_Body->SetTransform(m_Body->GetPosition(), tmp.x > 0 ? 0 : M_PI);
      }

      m_Body->ApplyLinearImpulse(tmp, m_Body->GetWorldCenter(), true);
      m_Body->SetLinearDamping(linear_damping);
      m_Body->SetAngularDamping(angular_damping);
      
      Notify(this, Util::Event::ENTITY_MOVE);
    }
  }
}
