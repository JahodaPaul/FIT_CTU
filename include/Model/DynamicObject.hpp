#pragma once

#include <utility>

#include "Model/Object.hpp"

namespace RG {
  namespace Model {
    class DynamicObject : public Object {
      public:
        DynamicObject(float x, float y, std::shared_ptr<b2World> world, std::string name);

        ~DynamicObject();

      private:
    };
  }
}
