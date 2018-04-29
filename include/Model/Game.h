//
// Created by pjahoda on 29.4.18.
//
#include <Controller/GameStateHandler.hpp>
#include <Model/Player.h>


#ifndef GAME_GAME_H
#define GAME_GAME_H

namespace RG{
    class Game{
    public:
        Game();
        void SetPlayer();
        std::shared_ptr<Player> GetPlayer();
    protected:
    private:
        std::shared_ptr<Player> player;
    };


}


#endif //GAME_GAME_H
