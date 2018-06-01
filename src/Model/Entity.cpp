#include "Model/Entity.hpp"

namespace RG {
  namespace Model {
    Entity::Entity(std::string name, unsigned int attack)
      : DynamicObject(name)
        , m_HP(100)
        , m_Defense(0)
        , m_Attack(attack)
    {
      Deleted = false;
      m_First = true;
    }

    Entity::~Entity() {}

    int Entity::GetAttackLevel(void) const { return m_Attack; }

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

    void Entity::Move(
        const b2Vec2& v, float linear_damping, float angular_damping)
    {
      if (v.x == 0 && v.y == 0) {
        if (m_First)
          m_First = false;
        else
          return;
      }
      DynamicObject::Move(v);
      Notify(this, Util::Event::ENTITY_MOVE);
    }

    unsigned int Entity::GetHP(void) const { return m_HP; }
  }
}
