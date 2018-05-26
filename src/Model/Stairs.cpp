#include "Model/Stairs.hpp"

namespace RG {
  namespace Model {
    Stairs::Stairs(bool up)
      : Object("Schody")
        , m_UP(up)
    {
    }

    Stairs::~Stairs() {}

    void Stairs::RecvAttack(int enemy_attack)
    {
      if (m_UP) {
        mainLog.Info("UP");
        Notify(this, Util::Event::FLOOR_UP);
      } else {
        mainLog.Info("DOWN");
        Notify(this, Util::Event::FLOOR_DOWN);
      }
    }
  }
}
