#pragma once

#include <Box2D/Box2D.h>
#include <memory>

#include "Model/Entity.hpp"

#include "common.hpp"

namespace RG {
  namespace Model {
    /**
     * \class ContactListener
     * \brief This class is for reacting to collisions.
     */
    class ContactListener : public b2ContactListener {
      public:
        /**
         * \function ContactListener
         * \brief constructor, connects the contact listener to the Box2D world
         * @param world Box2D world to which the contact listener should be
         * connected
         */
        ContactListener(std::shared_ptr<b2World> world);

        /**
         * \function ~ContactListener
         * \brief destructor, disconnects the contact listener from the world
         */
        ~ContactListener();

        /**
         * \function BeginContact
         * \brief resolves what happens when two objects collide
         * @param contact contains information about both fixtures that collided
         */
        virtual void BeginContact(b2Contact* contact);

        /**
         * \function EndContact
         * \brief manages what happens when the contact ends
         * @param contact contains information about both fixtures that collided
         */
        virtual void EndContact(b2Contact* b2Contact);

      private:
        /// Box2D world with all objects
        std::shared_ptr<b2World> m_World;
    };
  }
}
