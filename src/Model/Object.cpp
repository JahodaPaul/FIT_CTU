#include "Model/Object.hpp"

namespace RG {
  namespace Model {
    Object::Object(std::string name)
      : m_Body(NULL)
        , m_Name(name)
        , m_TypeBits(0)
        , m_AttackBits(0)
        , m_Width(0)
        , m_Height(0)
    {
      m_IsDead = false;
    }

    Object::~Object() {}

    std::string Object::GetName(void) const { return m_Name; }

    b2Vec2 Object::GetPosition(void) const
    {
      return m_Body ? m_Body->GetPosition() : b2Vec2(0, 0);
    }

    float Object::GetAngle(void) const { return m_Body ? m_Body->GetAngle() : 0; }

    void Object::AddShape(b2Shape* shapeDef, float density, uint16 category_bits,
        uint16 mask_bits, b2Body* body)
    {
      // Define the dynamic body fixture.
      b2FixtureDef fixtureDef;
      fixtureDef.shape = shapeDef;

      // Set the box density to be non-zero, so it will be dynamic.
      fixtureDef.density = density;

      // Override the default friction.
      fixtureDef.friction = 0.8f;

      fixtureDef.filter.categoryBits = category_bits;
      fixtureDef.filter.maskBits = mask_bits;

      if (body == nullptr)
        body = m_Body;

      if (body) {
        // Add the shape to the body.
        body->SetUserData(this);
        body->CreateFixture(&fixtureDef);
      }
    }

    bool Object::IsDead(void) { return m_IsDead; }

    int Object::GetAttackLevel(void) const { return 0; }

    void Object::RecvAttack(int enemy_attack)
    {
      mainLog.Warning(
          "RecvAttack in the Object class, this should never be called");
    }

    void Object::SetBits(unsigned int category_bits, unsigned int attack_bits)
    {
      m_TypeBits = category_bits;
      m_AttackBits = attack_bits;
    }

    unsigned int Object::GetAttack(void) const { return m_AttackBits; }

    unsigned int Object::GetType(void) const { return m_TypeBits; }

    float Object::GetWidth(void) const { return m_Width; }

    float Object::GetHeight(void) const { return m_Height; }

    void Object::SetDimensions(float w, float h)
    {
      m_Width = w;
      m_Height = h;
    }
  }
}
