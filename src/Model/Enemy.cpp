#include "Model/Enemy.hpp"

namespace RG {
  namespace Model {
    Enemy::Enemy()
      : Entity("Enemy", std::rand() % 18 + 1)
    {
      SetBits(BIT_ENEMY, BIT_PLAYER);
    }

    void Enemy::Move(b2Vec2 pos) { Entity::Move(pos); }
  }
}
