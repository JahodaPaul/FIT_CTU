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
    }

    Entity::~Entity() {}

    int Entity::GetAttackLevel(void) const { return m_Attack; }

    void Entity::RecvAttack(int enemy_attack, std::shared_ptr<b2World> world)
    {
      if (enemy_attack > m_Defense) {
        m_HP -= enemy_attack - m_Defense;
      }
      if (!m_IsDead && m_HP <= 0 && m_Body != nullptr) {
        m_IsDead = true;
        Notify(this, Util::Event::ENTITY_DEAD);
      }
    }

    void Entity::Move(
        const b2Vec2& v, float linear_damping, float angular_damping)
    {
      if (v.x == 0 && v.y == 0)
        return;
      Notify(this, Util::Event::ENTITY_MOVE);
      DynamicObject::Move(v);
    }
  }
}
