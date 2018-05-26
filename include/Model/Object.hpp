#pragma once

#include <Box2D/Box2D.h> // b2Body, b2Vec2
#include <iostream>
#include <memory>  // std::shared_ptr
#include <string>  // std::string
#include <utility> // std::pair

#include "common.hpp"

namespace RG {
  namespace Model {
    enum _category {
      BIT_WALL = 0x01,
      BIT_PLAYER = 0x02,
      BIT_ENEMY = 0x04,
    };

    /**
     * \class Object
     * \brief base class for all objects in the game
     */
    class Object {
      public:
        /**
         * \function Object
         * \brief constructor
         * @param name name of the object
         */
        Object(std::string name);

        /**
         * \function ~Object
         * \brief destructor
         */
        ~Object();

        /**
         * \function GetName
         * \brief returns name of the object
         */
        std::string GetName(void) const;

        /**
         * \function GetPosition
         * \brief returns position of the object (absolute, in the physical
         * world)
         */
        b2Vec2 GetPosition(void) const;

        /**
         * \function GetAngle
         * \brief return an angle in radians
         */
        float GetAngle(void) const;

        /**
         * \function AddShape
         * \brief  add shape to a body and define with what does it collide
         * @param shapeDef Box2D shape definition, should be ready for adding to
         * the body
         * @param density density of the newly created shape
         * @param category_bits what collision category does the object belong
         * to
         * @param mask_bits with what types of objects does the shape collide
         * with
         */
        void AddShape(b2Shape* shapeDef, float density, uint16 category_bits,
            uint16 mask_bits);

        /**
         * \function IsDead
         * \brief returns whether the object is dead or not
         */
        virtual bool IsDead(void);

        /**
         * \function GetAttackLevel
         * \brief returns the attack level
         */
        virtual int GetAttackLevel(void) const;

        /**
         * \function RecvAttack
         * \brief changes stats depending on defense level and enemy attack level
         * @param enemy_attack how strong the enemy is
         */
        virtual void RecvAttack(int enemy_attack);

        b2Body* m_Body;

        b2BodyDef* m_BodyDef;

      private:
        std::string m_Name;

      protected:
        bool m_IsDead;
    };
  }
}
