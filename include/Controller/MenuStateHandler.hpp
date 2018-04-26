#pragma once

#include <Controller/GameController.hpp>
#include <Controller/GameStateHandler.hpp>

namespace RG {
    class GameController;
    /**
     * \class MenuStateHandler
     * \brief
     */
    class MenuStateHandler : public GameStateHandler
    {
        public:
            MenuStateHandler();
            virtual ~MenuStateHandler();
            virtual void Update( float timeStep );
            virtual void GoToMainMenu( GameController * gameController );
            virtual void GoToGame( GameController * gameController );
            virtual void Quit( GameController * gameController );
    };
}
