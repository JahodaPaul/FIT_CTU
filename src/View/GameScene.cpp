#include "View/GameScene.hpp"

namespace RG {
    namespace View {
        GameScene::GameScene(View *view) :
            Scene( view )
            ,m_windowSize{ view->getWindow()->getSize() }
            ,m_firstFrame{ true }
        {
            player = std::make_shared<Player>(this, view->getLuaState());
            test_zombie = std::make_shared<Entity>(this, view->getLuaState(), "zombie");
            room = std::make_shared<RG::View::Room>();
            view->getGameController()->getModel().GetPlayer().AddObserver( player.get() );
            view->getGameController()->getModel().GetCurrentFloor().GetRoom().GetEntities()[0]->AddObserver( test_zombie.get() );
            view->getGameController()->getModel().GetCurrentFloor().AddObserver( player.get() );
            Notify( this, Util::Event::WINDOW_RESIZE );
        }

        GameScene::~GameScene() {
        }

        void GameScene::Update(View *view, float timeElapsed) {
            view->getGameController()->RunNPCWorld();
            view->getGameController()->MoveModel(player->GetPlayerSpeedX(),player->GetPlayerSpeedY());
            player->Update(view, timeElapsed);
            test_zombie->Update(view, timeElapsed);
        }

        void GameScene::Render(View *view) {
            this->DrawRoom(view);
            view->getWindow()->draw( *player );
            view->getWindow()->draw( *test_zombie );
            if (m_firstFrame) {
                m_firstFrame = false;
                room->SetSpriteScale( view->getWindow()->getView().getSize().x,view->getWindow()->getView().getSize().y);
            }
        }

        void GameScene::ManageInput(View *view) {

            std::shared_ptr<sf::RenderWindow> window = view->getWindow();
            sf::Event event;

            float speed = 30;

            while (window->pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);

                if(event.key.code == sf::Keyboard::Right){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedX(speed);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedX(speed * -1);
                    }
                }
                if(event.key.code == sf::Keyboard::Left){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedX(speed * -1);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedX(speed);
                    }
                }
                if(event.key.code == sf::Keyboard::Up){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedY(speed * -1);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedY(speed);
                    }
                }
                if(event.key.code == sf::Keyboard::Down){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedY(speed);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedY(speed * -1);
                    }
                }

                if (event.type == sf::Event::Closed) {
                    window->close();
                    view->getGameController()->Quit();
                    return;
                }

                if (event.type == sf::Event::Resized) {
                    m_windowSize = view->getWindow()->getView().getSize();
                    Notify( this, Util::Event::WINDOW_RESIZE );
                    room->SetSpriteScale( view->getWindow()->getView().getSize().x,view->getWindow()->getView().getSize().y);
                }
            }
        }

        void GameScene::DrawRoom(View *view) {
            room->DrawRoom(view->getGameController()->GetFloorLevel(),view->getGameController()->GetRoomId(),*view->getWindow());
            std::vector<bool> temporary = view->getGameController()->GetRoomDoors();
            room->DrawDoor(*view->getWindow(), temporary[0],temporary[1],temporary[2],temporary[3],view->getWindow()->getView().getSize().x,view->getWindow()->getView().getSize().y);
        }

        const sf::Vector2f & GameScene::getWindowSize() const {
            return m_windowSize;
        }
    }
}
