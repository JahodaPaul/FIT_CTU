#pragma once

#include <Box2D/Box2D.h> // b2Body, b2Vec2
#include <iostream>
#include <memory>  // std::shared_ptr
#include <string>  // std::string
#include <utility> // std::pair

namespace RG {
  namespace Model {
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

        void AddShape(b2Shape* shapeDef, float density = 0.1f);

        b2Body* m_Body;

        b2BodyDef* m_BodyDef;

      private:
        std::string m_Name;
    };
  }
}
