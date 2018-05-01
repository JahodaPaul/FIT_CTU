#pragma once

#include <memory>  // std::shared_ptr
#include <string>  // std::string
#include <utility> // std::pair

#include <Box2D/Box2D.h>

namespace RG {
  namespace Model {
    /**
     * \class Object
     * \brief
     */
    class Object {
      public:
        Object(float x, float y, std::shared_ptr<b2World> world, std::string, bool dynamic);

        ~Object();

        std::string GetName ( void ) const;

      protected:
        std::pair<float, float> m_Position;

      private:
        b2Body* m_Body; // FIXME (vanda,smart pointer)
        std::shared_ptr<b2World> m_World;
        std::string m_Name;
    };
  }
}
