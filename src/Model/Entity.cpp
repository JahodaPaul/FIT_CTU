#include "Model/Entity.hpp"

namespace RG {
  namespace Model {
    Entity::Entity(std::string name, unsigned int attack)
      : DynamicObject(name)
        , m_HP(100)
        , m_Defense(0)
    {
      m_Speed = 0;
      m_Attack = attack;
      Deleted = false;
      m_First = true;
    }

    Entity::~Entity() {}

    void Entity::RecvAttack(int enemy_attack)
    {
      if (m_Body == nullptr || m_IsDead || enemy_attack <= m_Defense)
        return;

      m_HP -= enemy_attack - m_Defense;
      if (m_HP > 0) {
        Notify(this, Util::Event::ENTITY_DAMAGED);
      } else {
        m_IsDead = true;
        Notify(this, Util::Event::ENTITY_DEAD);
      }
    }

    void Entity::Move(const b2Vec2& v)
    {
      if (v.x == 0 && v.y == 0) {
        if (m_First)
          m_First = false;
        else
          return;
      }
      DynamicObject::Move(v);
    }

    unsigned int Entity::GetHP(void) const { return m_HP; }

    void Entity::onNotify(Util::Subject* subject, Util::Event event) {}

    std::shared_ptr<RG::Model::Object> Entity::Shoot(
        const b2Vec2& target, std::shared_ptr<b2World> world)
    {
      std::shared_ptr<RG::Model::Object> shot
        = std::make_shared<RG ::Model::Shot>(target - m_Body->GetPosition(),
            m_Attack, GetType() | BIT_SHOT, GetAttack());

      b2BodyDef bodyDef;
      bodyDef.type = b2_dynamicBody;
      bodyDef.position = m_Body->GetPosition();
      shot->m_Body = world->CreateBody(&bodyDef);
      b2CircleShape circle;
      circle.m_p.Set(0, 0);
      float radius = 1;
      circle.m_radius = radius;
      shot->SetDimensions(2 * radius, 2 * radius);
      shot->AddShape(&circle, 30, shot->GetType(), BIT_PLAYER | BIT_WALL);
      return shot;
    }
  }
}
