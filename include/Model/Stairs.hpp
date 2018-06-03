#pragma once

#include "Model/Object.hpp"
#include "Util/Event.hpp"
#include "Util/Subject.hpp"

#include "common.hpp"

namespace RG {
  namespace Model {
    /**
     * \class Stairs
     * \brief stairs to another floor
     */
    class Stairs : public Object {
      public:
        Stairs(bool up = true);

        ~Stairs();

        void RecvAttack(int enemy_attack);

      private:
        bool m_UP;
    };
  }
}
