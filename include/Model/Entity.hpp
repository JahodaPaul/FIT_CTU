#pragma once

#include <string>
#include <utility>

#include "Model/DynamicObject.hpp"

namespace RG {
  namespace Model {
    /**
     * \class Entity
     * \brief generic entity object with basic attributes
     */
    class Entity : public DynamicObject {
      public:
        /// constructor
        Entity(std::string name, unsigned int attack = 20);

        /// destructor
        ~Entity();

        /// returns the attack level
        int GetAttackLevel(void) const;

        /// changes stats depending on defense level and enemy attack level
        void RecvAttack(int enemy_attack, std::shared_ptr<b2World> world);

      private:
        /// health points
        int m_HP;

        /// level of the entity
        int m_Level;

        /// defense level -- higher defense means higher ability to resist attack
        int m_Defense;

        /// current movement speed
        float m_Speed;

        /// attack level -- how much does the entity damage enemies during an attack
        int m_Attack;
    };
  }
}
