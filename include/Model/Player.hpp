//
// Created by pjahoda on 29.4.18.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <memory>

namespace RG{
    class Player{
    public:
        Player();
        std::pair<float,float> GetPosition() const;
        void Move(float x,float y);
    protected:
    private:
        float x;
        float y;
    };

}


#endif //GAME_PLAYER_H
