#pragma once

#include <cmath>
#include <string>
#include <utility>

#include "Model/Object.hpp"
#include "common.hpp"

namespace RG {
  namespace Model {
    /**
     * \class DynamicObject
     * \brief An object with an added option to move, also has dynamic body
     * instead of static
     */

    class DynamicObject : public Object {
      public:
        /**
         * \function DynamicObject
         * \brief constructor
         * @param name name of the object
         */
        DynamicObject(std::string name);

        /**
         * \function ~DynamicObject
         * \brief destructor
         */
        ~DynamicObject();

        /**
         * \function Move
         * \brief aplly force in a specified direction
         * @param v Box2D vector of movement - in which direction should the object
         * move
         * @param linear_damping how much is the object gradually slowed down
         * by surrounding environment
         * @param angular_damping how much is the object gradually slowed down when
         * rotating
         */
        virtual void Move(const b2Vec2& v);

      private:
    };
  }
}
