#include "Model/Player.hpp"

namespace RG {
  namespace Model {
    Player::Player(std::string name)
      : Entity(name, 100)
    {
      m_Speed = 40;
      SetBits(BIT_PLAYER, BIT_ENEMY | BIT_STAIRS);
      m_Room = nullptr;
    }

    void Player::ChangeFloor(unsigned int floor_idx)
    {
      if (floor_idx < m_Bodies.size()) {
        m_Body = m_Bodies[floor_idx];
      }
    }

    void Player::ChangeRoom(std::shared_ptr<RG::Model::Room> room)
    {
      m_Room = room;
    }

    std::shared_ptr<RG::Model::Object> Player::Shoot(
        const b2Vec2& target, std::shared_ptr<b2World> world)
    {
      if (m_Room != nullptr) {
        m_Room->AddObject(Entity::Shoot(target, world));
      }
      return nullptr;
    }
  }
}
