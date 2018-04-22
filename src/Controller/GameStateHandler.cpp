#include "Controller/GameStateHandler.hpp"

namespace RG {
    GameStateHandler::GameStateHandler() {
        std::cout << "MenuState Constructor" << std::endl;
    }
    void GameStateHandler::Update( float timeStep ) { }
    void GameStateHandler::GoToMainMenu( GameController * gameController ) {
        std::cout << "GameStateHandler GoToMainMenu" << std::endl;
    }
    void GameStateHandler::StartGame( GameController * gameController ) {
        std::cout << "GameStateHandler StartGame" << std::endl;
    }
    void GameStateHandler::Quit( GameController * gameController ) {
        std::cout << "GameStateHandler StopGame" << std::endl;
    }
}
