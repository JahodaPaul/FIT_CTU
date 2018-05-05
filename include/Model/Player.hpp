#ifndef MODEL_PLAYER_H
#define MODEL_PLAYER_H

#include <string>
#include <utility>

#include "Model/Entity.hpp"
//
// Created by pjahoda on 29.4.18.
//



namespace RG {
  namespace Model {
    /**
     * \class Player
     * \brief Object manipulated by user
     */
    class Player : public Entity {
      public:
        Player(float x, float y, std::shared_ptr<b2World> world, std::string name);

        ~Player();

        std::pair<float,float> GetPosition() const;

        void Move( void ); // FIXME (vanda)

      private:
        float x;
        float y;
    };
  }
}


#endif //MODEL_PLAYER_H
