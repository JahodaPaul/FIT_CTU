#include "Model/Enemy.hpp"

namespace RG {
  namespace Model {
    Enemy::Enemy()
      : Entity("Enemy", std::rand() % 18 + 1)
    {
      m_Speed = 20;
      SetBits(BIT_ENEMY, BIT_PLAYER);
    }

    void Enemy::Move(const b2Vec2& pos)
    {
      if (m_Body != nullptr) {
        Entity::Move(pos - m_Body->GetPosition());
      }
    }
  }
}
