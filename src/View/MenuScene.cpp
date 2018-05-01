#include "View/MenuScene.hpp"

namespace RG {
    MenuScene::MenuScene() {
        std::cout <<"menu scene constructor" << std::endl;
    }
    MenuScene::~MenuScene() {}
    void MenuScene::Update( View * view ) {}
    void MenuScene::Render( View * view ) {
        ImGui::GetStyle().WindowBorderSize = 0;
        ImGui::SetNextWindowBgAlpha(0);
        ImGui::SetNextWindowPos(ImVec2(view->getWindow()->getSize().x / 2  - m_menuWidth/2, view->getWindow()->getSize().y / 2 - m_menuHeight/2));
        ImGui::SetNextWindowSize({m_menuWidth,m_menuHeight});

        ImGui::Begin("", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove );
        if (ImGui::Button("New Game", ImVec2(m_itemWidth,m_itemHeight))) {
            view->getGameController()->GoToGame();
        }
        {
            if (ImGui::Button("Higscores", ImVec2(m_itemWidth,m_itemHeight))) { }
            if (ImGui::Button("Exit", ImVec2(m_itemWidth,m_itemHeight)))
                view->getGameController()->Quit();
        }
        ImGui::End();
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
