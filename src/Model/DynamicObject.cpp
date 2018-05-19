#include "Model/DynamicObject.hpp"

namespace RG {
  namespace Model {
    DynamicObject::DynamicObject(std::string name)
      : Object(name)
    {
    }

    DynamicObject::~DynamicObject() {}

    void DynamicObject::Move(
        const b2Vec2& v, float linear_damping, float angular_damping)
    {
      if (v.y != 0) {
        double angle = std::atan(v.x / v.y);
        if(angle < 0) angle += M_PI;
        else if(angle == 0) angle += M_PI/2;
        if(v.y < 0) angle += M_PI;
        m_Body->SetTransform(
            m_Body->GetPosition(), angle);
      } else {
        m_Body->SetTransform(m_Body->GetPosition(), v.x > 0 ? 0 : M_PI);
      }

      m_Body->ApplyForce(v, m_Body->GetWorldCenter(), true);
      m_Body->SetLinearDamping(linear_damping);
      m_Body->SetAngularDamping(angular_damping);
    }
  }
}
