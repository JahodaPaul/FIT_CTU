#pragma once

#include <string>
#include <utility>

#include "Model/DynamicObject.hpp"
#include "Model/Shot.hpp"
#include "Util/Observer.hpp"

namespace RG {
  namespace Model {
    /**
     * \class Entity
     * \brief generic entity object with basic attributes
     */
    class Entity : public DynamicObject, public Util::Observer {
      public:
        /**
         * \function Entity
         * \brief constructor
         * @param name name of the entity
         * @param attack how much is the entity going to damage others
         */
        Entity(std::string name, unsigned int attack = 20);

        /**
         * \function ~Entity
         * \brief destructor
         */
        virtual ~Entity();

        /**
         * \function RecvAttack
         * \brief changes stats depending on defense level and enemy attack level
         * @param enemy_attack how strong is the enemy
         */
        void RecvAttack(int enemy_attack);

        /**
         * \function Move
         * \brief moves the entity and sends a notification to the observer
         * @param v Box2D vector of movement - in which direction should the object
         * move
         * @param linear_damping how much is the object gradually slowed down
         * by surrounding environment
         * @param angular_damping how much is the object gradually slowed down when
         * rotating
         */
        virtual void Move(const b2Vec2& v);

        /**
         * \function GetHP
         * \brief returns how many health points does the entity have(maximum is
         * 100, can be negative)
         */
        unsigned int GetHP(void) const;

        virtual std::shared_ptr<RG::Model::Object> Shoot(
            const b2Vec2& target, std::shared_ptr<b2World> world);

        virtual void onNotify(Util::Subject* subject, Util::Event event) override;

      protected:
        /// health points
        int m_HP;

        /// level of the entity
        int m_Level;

        /// defense level -- higher defense means higher ability to resist attack
        int m_Defense;

        /// whether the first zero movement of the game has already been made or not
        bool m_First;
    };
  }
}
