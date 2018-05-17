#include "View/View.hpp"

namespace RG {
    namespace View {
        View::View(Controller::GameController *controller, std::pair<int,int> windowSize, const char *windowTitle)
                : m_gameControllet(controller),
                  m_ImguiDemo(false) {
            m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowSize.first, windowSize.second),
                                                          windowTitle, sf::Style::Default,
                                                          sf::ContextSettings{0u, 0u, 4u, 1u, 1u, 0u, false});
            //synchromize refresh rate with monitor refresh rate
            m_window->setVerticalSyncEnabled(true);

            // Invert y axis and zoom in
            //m_view.reset(sf::FloatRect(0, windowSize.y, 2*windowSize.x, 2*-windowSize.y));

//            m_window->setVerticalSyncEnabled(true);
            m_window->setFramerateLimit(60);
            m_window->setKeyRepeatEnabled( false );

            // Apply setting
            //m_window.setView(m_view);

            m_activeScene = SCENE::MENU_SCENE;
            m_mapOfGameScenes[SCENE::MENU_SCENE] = std::shared_ptr<Scene>(new MenuScene());
            m_mapOfGameScenes[SCENE::GAME_SCENE] = std::shared_ptr<Scene>(new GameScene());

            //initialize imgui
            ImGui::SFML::Init(*m_window);
            ImGuiIO &io = ImGui::GetIO();
            io.KeyMap[ImGuiKey_Space] = sf::Keyboard::Return;
            io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;

            m_console.RegisterFunction("quit", std::function<int(void)>([this]() { return m_gameControllet->Quit(); }));
            m_console.RegisterFunction("imgui_demo", std::function<int(void)>([this]() {
                m_ImguiDemo = !m_ImguiDemo;
                return 0;
            }));
            m_console.RegisterFunction("go_to_game_scene", std::function<int(void)>([this]() {
                m_gameControllet->GoToGame();
                return 0;
            }));
            m_console.RegisterFunction("go_to_menu_scene", std::function<int(void)>([this]() {
                m_gameControllet->GoToMainMenu();
                return 0;
            }));

            m_soundManager.PlayMusic("frankum");
        }

        View::~View() {}

        void View::ManageInput() {
            m_mapOfGameScenes[m_activeScene]->ManageInput(this);
        }

        void View::Update() {
            m_timeElapsed = m_clock.restart();
            m_mapOfGameScenes[m_activeScene]->Update(this, m_timeElapsed.asSeconds());
        }

        void View::Render() {
            //ImGui
            ImGui::SFML::Update(*m_window, m_timeElapsed);
            m_window->clear({0, 0, 0, 255});

            //FPS counter
            ImGui::SetNextWindowPos({m_window->getSize().x - 90.f, 0});
            ImGui::SetNextWindowSize({90, 20});
            ImGui::Begin("FPS", NULL,
                         ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
            ImGui::End();

            //DEBUG
            if (m_ImguiDemo)
                ImGui::ShowDemoWindow();
            m_console.Draw();

            m_mapOfGameScenes[m_activeScene]->Render(this);

            //ImGui
            ImGui::SFML::Render(*m_window);
            //display window content

            m_window->display();
        }

        std::shared_ptr<sf::RenderWindow> View::getWindow() {
            return m_window;
        }

        Controller::GameController *View::getGameController() const {
            return m_gameControllet;
        }

        void View::setActiveView(SCENE scene) {
            m_activeScene = scene;
        }

        const sf::View & View::GetView() {
            return m_window->getView();
        }
    }
}
