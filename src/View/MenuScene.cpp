#include "View/MenuScene.hpp"

namespace RG {
    MenuScene::MenuScene() {
        std::cout <<"menu scene constructor" << std::endl;
    }
    MenuScene::~MenuScene() {}
    void MenuScene::Update( View * view ) {}
    void MenuScene::Render( View * view ) {
        ImGui::SetNextWindowBgAlpha(0);
        ImGui::GetStyle().WindowBorderSize = 0;
        ImGui::Begin("", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove );
        if (ImGui::Button("New Game", ImVec2(100,50))) {
        }
        if (ImGui::Button("Higscores", ImVec2(100,50))) {
        }
        if (ImGui::Button("Exit", ImVec2(100,50)))
            view->getGameController()->Quit();
        ImGui::SetWindowPos(ImVec2((view->getWindow()->getSize().x) / 2  - ImGui::GetWindowWidth() / 2, view->getWindow()->getSize().y / 2 - ImGui::GetWindowHeight() / 2), true);
        ImGui::End();

        view->getWindow()->clear({255,0,0,255});

        ImGui::SFML::Render(*view->getWindow());
        view->getWindow()->display();
    }
    void MenuScene::ManageInput( View * view ) {
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
