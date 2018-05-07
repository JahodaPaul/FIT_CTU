#include "Controller/GameController.hpp"

namespace RG {
    GameController::GameController() : m_running( false ) {
        std::cout << "GameController Constructor" << std::endl;
        m_mapOfGameStateHandlers[STATES::MAIN_MENU] = std::shared_ptr<GameStateHandler>( new MenuStateHandler() );
        m_mapOfGameStateHandlers[STATES::RUNNING] = std::shared_ptr<GameStateHandler>( new GameStateHandler() );
        m_GameState = STATES::MAIN_MENU;
        m_view = std::make_shared<RG::View::View>(this);
        m_model = std::make_shared<RG::Model::Model>();
    }
    GameController::~GameController() {}

    std::pair<float, float> GameController::GetPlayerPos() const
    {
      return m_model->GetPlayerPosition();
    }

    float GameController::GetPlayerAngle() const
    {
      return m_model->GetPlayerRotation();
    }

    void GameController::MoveModel(float x, float y) const
    {
      return m_model->Move(x, y);
    }

    void GameController::StepModel(float step) const
    {
      return m_model->Step(step);
    }

    void GameController::Run() {
        m_running = true;
        std::cout << "Running" << std::endl;
        while ( m_running ) {
            if ( m_GameState == STATES::RUNNING ) {
                //TODO(vojta) update game model
                StepModel(1000.0f/16.0f);
            }
            m_view->ManageInput();
            m_view->Update();
            m_view->Render();
        }
    }
    int GameController::Quit() {
        std::cout <<"quit" << std::endl;
        m_running = false;
        return 0;
    }
    void GameController::setState( STATES s ) {
        m_GameState = s;
    }
    void GameController::Update( float timeStep ) { }
    void GameController::GoToMainMenu() {
        m_mapOfGameStateHandlers[m_GameState]->GoToMainMenu( this );
        m_view->setActiveView( RG::View::SCENE::MENU_SCENE );
    }
    void GameController::GoToGame() {
        m_mapOfGameStateHandlers[m_GameState]->GoToGame( this );
        m_view->setActiveView( RG::View::SCENE::GAME_SCENE );
        m_view->SetPlayer();
        m_view->GetPlayer()->GetAnimation()->goToFrame(0);
        m_view->GetPlayer()->GetAnimation()->startAnimation();
        m_model = std::make_shared<RG::Model::Model>();
    }
    void GameController::setActiveGameState( STATES state ) {
        m_GameState = state;
    }

    int GameController::GetRoomId(){
        return m_model->GetRoomId();
    }

    int GameController::GetFloorLevel() {
        return m_model->GetFloorLevel();
    }

    std::vector<bool> GameController::GetRoomDoors() {
        return m_model->GetRoomDoors(this->m_model->GetRoomId());
    }


}
