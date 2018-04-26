#include "View/GameScene.hpp"

namespace RG {
    GameScene::GameScene() {
    }
    GameScene::~GameScene() {
    }
    void GameScene::Update( View * view ) {
    }
    void GameScene::Render( View * view ) {
    }
    void GameScene::ManageInput( View * view ) {
        std::shared_ptr<sf::RenderWindow> window = view->getWindow();
        sf::Event event;
        while (window->pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window->close();
                view->getGameController()->Quit();
                return;
            }
        }
    }
}
