#include "View/View.hpp"

namespace RG {
    View::View( GameController * controller, Vect2f windowSize, const char * windowTitle ) 
        : m_gameControllet( controller ),
        m_ImguiDemo( false ),
        m_console( &m_api )
    { m_window = std::make_shared<sf::RenderWindow>( sf::VideoMode( windowSize.x, windowSize.y ),
                windowTitle, sf::Style::Default,
                sf::ContextSettings{ 0u, 0u, 4u, 1u, 1u, 0u, false } );
        //synchromize refresh rate with monitor refresh rate
        m_window->setVerticalSyncEnabled(true);

        // Invert y axis and zoom in
        //m_view.reset(sf::FloatRect(0, windowSize.y, 2*windowSize.x, 2*-windowSize.y));

        m_window->setVerticalSyncEnabled(true);

        // Apply setting
        //m_window.setView(m_view);
        
        m_activeScene = SCENE::MENU_SCENE;
        m_mapOfGameScenes[m_activeScene] = std::shared_ptr<Scene>( new MenuScene() );

        //initialize imgui
        ImGui::SFML::Init(*m_window);
        ImGuiIO& io = ImGui::GetIO();
        io.KeyMap[ImGuiKey_Space] = sf::Keyboard::Return;
        io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;

        m_api["quit"] = std::function<void(void)>( [this](){ m_gameControllet->Quit(); } );
        m_api["imgui_demo"] = std::function<void(void)>( [this](){ m_ImguiDemo = !m_ImguiDemo; } );
    }
    View::~View() {}
    void View::ManageInput() {
        m_mapOfGameScenes[m_activeScene]->ManageInput( this );
    }
    void View::Update() {
        m_mapOfGameScenes[m_activeScene]->Update( this );
    }
    void View::Render() {
        ImGui::SFML::Update(*m_window, m_clock.restart());
        if ( m_ImguiDemo )
            ImGui::ShowDemoWindow();
        //ShowDebugWindow();
        m_console.Draw();
        m_mapOfGameScenes[m_activeScene]->Render( this );
    }
    std::shared_ptr<sf::RenderWindow> View::getWindow() {
        return m_window;
    }
    GameController * View::getGameController() {
        return m_gameControllet;
    }
    sf::Clock & View::getClock() {
        return m_clock;
    }
    void View::ShowDebugWindow() {
        ImGui::SetNextWindowPos({0,0}, ImGuiCond_FirstUseEver);
        ImGui::Begin("Debug window", NULL);
        for ( auto & it : m_api ) {
            if ( ImGui::Button(it.first.c_str()) )
                it.second();
        }
        ImGui::End();
    }
};
