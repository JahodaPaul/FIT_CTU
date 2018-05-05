#include "Model/Entity.hpp"

namespace RG {
  namespace Model {
    Entity::Entity(b2BodyDef* body, std::string name)
      : DynamicObject(body, name)
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
