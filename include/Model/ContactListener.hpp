#pragma once

#include <Box2D/Box2D.h>
#include <memory>

#include "Model/Entity.hpp"

namespace RG {
  namespace Model {
    class ContactListener : public b2ContactListener {
      public:
        ContactListener(std::shared_ptr<b2World> world);

        ~ContactListener();

        virtual void BeginContact(b2Contact* contact);

        virtual void EndContact(b2Contact* b2Contact);

      private:
        std::shared_ptr<b2World> m_World;
    };
  }
}
