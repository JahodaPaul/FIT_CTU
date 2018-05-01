#include "Controller/MenuStateHandler.hpp"

namespace RG {
    MenuStateHandler::MenuStateHandler() : GameStateHandler() {
        std::cout << "MenuState Constructor" << std::endl;
    }
    MenuStateHandler::~MenuStateHandler() { }
    void MenuStateHandler::Update( float timeStep ) { }
    void MenuStateHandler::GoToMainMenu( GameController * gameController ) {
        std::cout << "MenuState GoToMainMenu" << std::endl;
    }
    void MenuStateHandler::GoToGame( GameController * gameController ) {
        std::cout << "MenuState StartGame" << std::endl;
        gameController->setActiveGameState(STATES::RUNNING);
    }
    void MenuStateHandler::Quit( GameController * gameController ) {
        std::cout << "MenuState StopGame" << std::endl;
    }
}
