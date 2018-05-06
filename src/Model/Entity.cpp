#include "Model/Entity.hpp"

namespace RG {
  namespace Model {
    Entity::Entity(std::string name)
      : DynamicObject(name)
    {
    }

    Entity::~Entity() {}

    int Entity::GetAttackLevel(void) const { return m_Attack; }

    void Entity::RecvAttack(int enemy_attack)
    {
      // TODO (vanda)
    }
  }
}
