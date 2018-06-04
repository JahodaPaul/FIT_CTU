#pragma once

#include <Box2D/Box2D.h> // b2Body, b2Vec2
#include <iostream>
#include <memory>  // std::shared_ptr
#include <string>  // std::string
#include <utility> // std::pair

#include "Util/Event.hpp"
#include "Util/Subject.hpp"
#include "common.hpp"

namespace RG {
  namespace Model {
    enum _category {
      BIT_WALL = 0x01,
      BIT_PLAYER = 0x02,
      BIT_ENEMY = 0x04,
      BIT_STAIRS = 0x08,
      BIT_SHOT = 0x10
    };

    /**
     * \class Object
     * \brief base class for all objects in the game
     */
    class Object : public Util::Subject {
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
         * @param body body to which the shape should be added, default is
         * m_Body
         */
        void AddShape(b2Shape* shapeDef, float density, uint16 category_bits,
            uint16 mask_bits, b2Body* body = nullptr);

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

        void SetBits(unsigned int category_bits, unsigned int attack_bits);

        unsigned int GetAttack(void) const;

        unsigned int GetType(void) const;

        float GetWidth(void) const;

        float GetHeight(void) const;

        void SetDimensions(float w, float h);

        virtual void Move(const b2Vec2& pos);

        virtual std::shared_ptr<RG::Model::Object> Shoot(
            const b2Vec2& target, std::shared_ptr<b2World> world);

        void Contact(void);

        b2Body* m_Body;

        /// whether the body is deleted from the Box2D world which makes the obejct
        /// prepared for destruction
        bool Deleted;

      private:
        std::string m_Name;

        unsigned int m_TypeBits;
        unsigned int m_AttackBits;

      protected:
        bool m_IsDead;

        float m_Width;

        float m_Height;

        /// current movement speed
        float m_Speed;

        /// attack level -- how much does the entity damage enemies during an attack
        int m_Attack;
    };
  }
}
