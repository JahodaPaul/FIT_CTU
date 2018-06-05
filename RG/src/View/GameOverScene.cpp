#include "View/GameOverScene.hpp"

namespace RG {
    namespace View {
        GameOverScene::GameOverScene(View *view) :
            Scene( view )
        {
            mainLog.Info("Game over scene constructor");
            this->background_texture.loadFromFile("/usr/share/RG/assets/graphics/backgrounds/screens/StartScreen.png");
            this->background.setTexture(this->background_texture);
        }

        GameOverScene::~GameOverScene() {}

        void GameOverScene::Update(View *view, float timeElapsed) {
        }

        void GameOverScene::Render(View *view) {

            if(view->GetView().getSize().x != this->windowX || view->GetView().getSize().y != this->windowY){
                this->windowX = view->GetView().getSize().x;
                this->windowY = view->GetView().getSize().y;
                this->background.setScale(this->windowX/this->background.getLocalBounds().width,this->windowY/this->background.getLocalBounds().height);
            }
            view->getWindow()->draw(this->background);

            ImGui::GetStyle().WindowBorderSize = 0;
            ImGui::SetNextWindowBgAlpha(0);
            ImGui::SetNextWindowPos(ImVec2(view->getWindow()->getSize().x / 3 - m_menuWidth / 2,
                        view->getWindow()->getSize().y / 2 - m_menuHeight / 2));
            ImGui::SetNextWindowSize({m_menuWidth, m_menuHeight});

            ImGui::Begin("", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            ImGui::Text("Game Over");
            if (ImGui::Button("Exit", ImVec2(m_itemWidth, m_itemHeight)))
                view->getGameController()->Quit();
            ImGui::End();
        }

        void GameOverScene::ManageInput(View *view) {
            std::shared_ptr<sf::RenderWindow> window = view->getWindow();
            sf::Event event;
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
