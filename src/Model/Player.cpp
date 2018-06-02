#include "Model/Player.hpp"

namespace RG {
  namespace Model {
    Player::Player(std::string name)
      : Entity(name, 100)
    {
      SetBits(BIT_PLAYER, BIT_ENEMY | BIT_STAIRS);
    }

    void Player::ChangeFloor(unsigned int floor_idx)
    {
      if (floor_idx < m_Bodies.size()) {
        mainLog.Info("changing body");
        m_Body = m_Bodies[floor_idx];
      }
    }
  }
}
