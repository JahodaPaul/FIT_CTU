#include "View/GameScene.hpp"

namespace RG {
    namespace View {
        GameScene::GameScene(View *view) :
            Scene( view ),
            m_firstFrame{ true } {
            player = std::make_shared<Player>();
            room = std::make_shared<RG::View::Room>();
            view->getGameController()->getModel().GetPlayer().AddObserver( player.get() );
        }

        GameScene::~GameScene() {
        }

        void GameScene::Update(View *view, float timeElapsed) {
            view->getGameController()->RunNPCWorld();
            view->getGameController()->MoveModel(this->GetPlayerSpeedX(),this->GetPlayerSpeedY());
            this->UpdatePlayer(view, timeElapsed);
        }

        void GameScene::Render(View *view) {
            this->DrawRoom(view);
            this->DrawPlayer(view);
            if (m_firstFrame) {
                m_firstFrame = false;
                player->SetPlayerScale( view->getWindow()->getView().getSize().x,view->getWindow()->getView().getSize().y);
                room->SetSpriteScale( view->getWindow()->getView().getSize().x,view->getWindow()->getView().getSize().y);
            }
        }

        void GameScene::ManageInput(View *view) {

            std::shared_ptr<sf::RenderWindow> window = view->getWindow();
            sf::Event event;

            float speed = 3;

            while (window->pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);

                if(event.key.code == sf::Keyboard::Right){
                    if (event.type == sf::Event::KeyPressed) {
                        this->SetPlayerSpeedX(speed);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        this->SetPlayerSpeedX(speed * -1);
                    }
                }
                if(event.key.code == sf::Keyboard::Left){
                    if (event.type == sf::Event::KeyPressed) {
                        this->SetPlayerSpeedX(speed * -1);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        this->SetPlayerSpeedX(speed);
                    }
                }
                if(event.key.code == sf::Keyboard::Up){
                    if (event.type == sf::Event::KeyPressed) {
                        this->SetPlayerSpeedY(speed * -1);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        this->SetPlayerSpeedY(speed);
                    }
                }
                if(event.key.code == sf::Keyboard::Down){
                    if (event.type == sf::Event::KeyPressed) {
                        this->SetPlayerSpeedY(speed);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        this->SetPlayerSpeedY(speed * -1);
                    }
                }

                if (event.type == sf::Event::Closed) {
                    window->close();
                    view->getGameController()->Quit();
                    return;
                }

                if (event.type == sf::Event::Resized) {
                    player->SetPlayerScale( view->getWindow()->getView().getSize().x,view->getWindow()->getView().getSize().y);
                    room->SetSpriteScale( view->getWindow()->getView().getSize().x,view->getWindow()->getView().getSize().y);
                }
            }
        }
        void GameScene::UpdatePlayer(View * view, float timeElapsed) {//float relativeMoveX, float relativeMoveY,
            player->UpdatePlayer(view, timeElapsed);
        }

        void GameScene::DrawPlayer(View *view) {
            player->DrawPlayer(*view->getWindow());
        }

        void GameScene::DrawRoom(View *view) {
            room->DrawRoom(view->getGameController()->GetFloorLevel(),view->getGameController()->GetRoomId(),*view->getWindow());
            std::vector<bool> temporary = view->getGameController()->GetRoomDoors();
            room->DrawDoor(*view->getWindow(), temporary[0],temporary[1],temporary[2],temporary[3],view->getWindow()->getView().getSize().x,view->getWindow()->getView().getSize().y);
        }

        void GameScene::SetPlayerSpeedX(float x) {
            this->player->SetPlayerSpeedX(x);
        }

        void GameScene::SetPlayerSpeedY(float y) {
            this->player->SetPlayerSpeedY(y);
        }

        float GameScene::GetPlayerSpeedX() {
            return this->player->GetPlayerSpeedX();
        }

        float GameScene::GetPlayerSpeedY() {
            return this->player->GetPlayerSpeedY();
        }

    }
}
