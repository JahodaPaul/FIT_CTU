#include "Model/Entity.hpp"

namespace RG {
  namespace Model {
    Entity::Entity(std::string name, unsigned int attack)
      : DynamicObject(name)
        , m_HP(100)
        , m_Defense(0)
        , m_Attack(attack)
    {
    }

    Entity::~Entity() {}

    int Entity::GetAttackLevel(void) const { return m_Attack; }

    void Entity::RecvAttack(int enemy_attack, std::shared_ptr<b2World> world)
    {
      if (enemy_attack > m_Defense) {
        m_HP -= enemy_attack - m_Defense;
      }
      if (m_HP <= 0 && m_Body != nullptr) {
        m_IsDead = true;
      }
    }
  }
}
