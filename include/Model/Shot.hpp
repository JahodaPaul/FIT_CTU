#pragma once

#include "Model/DynamicObject.hpp"
#include "Model/Object.hpp"
#include "Util/Event.hpp"
#include "Util/Subject.hpp"

namespace RG {
  namespace Model {
    class Shot : public DynamicObject {
      public:
        Shot(const b2Vec2& target, unsigned int attack, unsigned int category_bits,
            unsigned int attack_bits);

        void Move(const b2Vec2& pos);

        void RecvAttack(int enemy_attack);
        
      private:
        b2Vec2 m_Target;
    };
  }
}
