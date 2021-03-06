#include "Controller/GameController.hpp"

namespace RG { namespace Controller {
    GameController::GameController() 
        :m_running( false )
        ,m_updateModel{ true }
    {
        mainLog.Info("GameController Constructor");
        m_mapOfGameStateHandlers[STATES::MAIN_MENU] = std::shared_ptr<StateHandler>( new MenuStateHandler() );
        m_mapOfGameStateHandlers[STATES::RUNNING] = std::shared_ptr<StateHandler>( new GameStateHandler() );
        m_GameState = STATES::MAIN_MENU;
        m_model = std::make_shared<RG::Model::Model>();
        m_NPCWorld  = std::make_shared<RG::NPC::NPCWorldCycle>();
        m_view = std::make_shared<RG::View::View>(this);
        m_howOftenRunNPCWorld = 0;
    }
    GameController::~GameController() {}

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
        mainLog.Info("Game running");
        while ( m_running ) {
            if ( m_GameState == STATES::RUNNING && m_updateModel ) {
                //TODO(vojta) update game model
                StepModel(m_clock.restart().asMilliseconds());
            }
            m_view->ManageInput();
            m_view->Update();
            m_view->Render();
        }
    }

    void GameController::RunNPCWorld(){
        if (m_howOftenRunNPCWorld % 100 == 0){
            this->m_NPCWorld->Run();
            m_howOftenRunNPCWorld = 0;
        }
        m_howOftenRunNPCWorld++;
    }

    int GameController::Quit() {
        mainLog.Info("Game quit");
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
    
    Model::Model & GameController::getModel() {
        return *m_model;
    }
    NPC::NPCWorldCycle & GameController::getNPCWorldCycle() {
        return *m_NPCWorld;
    }
    void GameController::StopModelUpdate() {
        m_updateModel = false;
    }
    void GameController::StartModelUpdate() {
        m_updateModel = true;
    }
} }
