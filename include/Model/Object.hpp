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
        Object(std::string);

        ~Object();

        std::string GetName(void) const;

        b2Vec2 GetPosition(void) const;

        /// return an angle in degrees
        float GetAngle(void) const;

        /// add shape to a body and define with what does it collide
        void AddShape(b2Shape* shapeDef, float density, uint16 category_bits,
            uint16 mask_bits);

        b2Body* m_Body;

        b2BodyDef* m_BodyDef;

        virtual bool IsDead(void);

        /// returns the attack level
        virtual int GetAttackLevel(void) const;

        /// changes stats depending on defense level and enemy attack level
        virtual void RecvAttack(int enemy_attack, std::shared_ptr<b2World> world)
          = 0;

      private:
        std::string m_Name;

      protected:
        bool m_IsDead;
    };
  }
}
