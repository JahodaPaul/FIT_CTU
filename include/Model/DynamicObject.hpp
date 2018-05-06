#pragma once

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
        DynamicObject(std::string name);

        ~DynamicObject();

        void Move(const b2Vec2& v);

      private:
    };
  }
}
