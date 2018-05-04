#pragma once

#include "View/Scene.hpp"
#include "View/View.hpp"

#include <iostream>

namespace RG {
    namespace View {
        class MenuScene : public Scene {
        public:
            MenuScene();

            virtual ~MenuScene();

            virtual void Update(View *view);

            virtual void Render(View *view);

            virtual void ManageInput(View *view);

        private:
            const float m_itemWidth = 100;
            const float m_itemHeight = 50;
            const float m_menuWidth = m_itemWidth + 20;
            const float m_menuHeight = m_itemHeight * 3 + 30;

            sf::Texture background_texture;
            sf::Sprite background;
            float windowX;
            float windowY;
        };
    }
}
