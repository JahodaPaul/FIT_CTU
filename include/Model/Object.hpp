#pragma once

#include <Box2D/Box2D.h> // b2Body, b2Vec2
#include <iostream>
#include <memory>  // std::shared_ptr
#include <string>  // std::string
#include <utility> // std::pair

namespace RG {
  namespace Model {
    enum _category {
      BIT_WALL = 0x01,
      BIT_PLAYER = 0x02,
      BIT_ENEMY = 0x04,
    };

    /**
     * \class Object
     * \brief
     */
    class Object {
      public:
        Object(std::string);

        ~Object();

        std::string GetName(void) const;

        b2Vec2 GetPosition(void) const;

        float GetAngle(void) const;

        void AddBody(b2Body* body);

        void AddShape(b2Shape* shapeDef, float density, uint16 category_bits,
            uint16 mask_bits);

        b2Body* m_Body;

        b2BodyDef* m_BodyDef;

        bool IsDead(void);

      private:
        std::string m_Name;

      protected:
        bool m_IsDead;
    };
  }
}
