#pragma once

#include <memory>
#include <iostream>

namespace RG {
    class GameController;
    /**
     * \class GameStateHandler
     * \brief
     */
    class GameStateHandler
    {
        public:
            GameStateHandler();
            virtual ~GameStateHandler(){}
            virtual void GoToMainMenu( GameController * gameController );
            virtual void GoToGame( GameController * gameController );
            virtual void Quit( GameController * gameController );
            virtual void Update( float timeStep );
    };
}
