#include "Model/Shot.hpp"

namespace RG {
  namespace Model {
    Shot::Shot(const b2Vec2& target, unsigned int attack,
        unsigned int category_bits, unsigned int attack_bits)
      : DynamicObject("Shot")
        , m_Target(target)
    {
      SetBits(BIT_SHOT | category_bits, attack_bits);
      m_Speed = 10;
      m_Attack = attack;
    }

    void Shot::Move(const b2Vec2& pos) { DynamicObject::Move(m_Target); }

    void Shot::RecvAttack(int enemy_attack)
    {
      m_IsDead = true;
      Notify(this, RG::Util::SHOT_CRASHED);
    }
  }
}
