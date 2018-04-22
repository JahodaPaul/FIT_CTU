#include "Controller/GameController.hpp"

namespace RG {
    GameController::GameController() : m_running( false ) {
        std::cout << "GameController Constructor" << std::endl;
        m_mapOfGameStateHandlers[STATES::MAIN_MENU] = std::shared_ptr<GameStateHandler>( new MenuStateHandler() );
        m_GameState = STATES::MAIN_MENU;
        m_view = std::make_shared<View>(this);
    }
    GameController::~GameController() {}

    void GameController::Run() {
        m_running = true;
        std::cout << "Running" << std::endl;
        while ( m_running ) {
            m_view->ManageInput();
            m_view->Update();
            m_view->Render();
        }
    }
    void GameController::Quit() {
        std::cout <<"quit" << std::endl;
        m_running = false;
    }
    void GameController::setState( STATES s ) {
        m_GameState = s;
    }
    void GameController::Update( float timeStep ) { }
    void GameController::GoToMainMenu() {
        m_mapOfGameStateHandlers[m_GameState]->GoToMainMenu( this );
    }
    void GameController::StartGame() {
        m_mapOfGameStateHandlers[m_GameState]->StartGame( this );
    }
}
