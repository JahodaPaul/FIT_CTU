#include <Model/Entity.hpp>

namespace RG {
  namespace Model {
    Entity::Entity(float x, float y, std::shared_ptr<b2World> world, std::string name) : DynamicObject(x, y, world, name){
    }

    Entity::~Entity(){
    }

    int Entity::GetAttackLevel ( void ) const {
      return m_Attack;
    }

    void Entity::RecvAttack ( int enemy_attack ) {
      // TODO (vanda)
    }
  }
}
