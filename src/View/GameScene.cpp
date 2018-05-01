#include "View/GameScene.hpp"
#include "View/Animation.hpp"

namespace RG {
    namespace View {
        GameScene::GameScene() {
        }

        GameScene::~GameScene() {
        }

        void GameScene::Update(View *view) {

        }

        void GameScene::Render(View *view) {
//        view->UpdatePlayer(0.0f,0.0f);
            view->DrawPlayer();
        }

        void GameScene::ManageInput(View *view) {

            std::shared_ptr<sf::RenderWindow> window = view->getWindow();
            sf::Event event;

            float speed = 0.1;
            float x = 0, y = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                x += speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                x -= speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                y += speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                y -= speed;
            }
            view->UpdatePlayer(x, y);
            while (window->pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);
                if (event.type == sf::Event::Closed) {
                    window->close();
                    view->getGameController()->Quit();
                    return;
                }
            }
        }
    }
}
