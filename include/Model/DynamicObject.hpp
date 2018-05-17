#pragma once

#include <cmath>
#include <utility>

#include "Model/Object.hpp"

namespace RG {
  namespace Model {
    /**
     * \class DynamicObject
     * \brief An object with an added option to move, also has dynamic body
     * instead of static
     */

    class DynamicObject : public Object {
      public:
        /// constructor
        DynamicObject(std::string name);

        /// destructor
        ~DynamicObject();

        /// aplly force in a specified direction
        void Move(const b2Vec2& v, float linear_damping = 0.04f,
            float angular_damping = 2.0f);

      private:
    };
  }
}
