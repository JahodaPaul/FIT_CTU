#pragma once

#include "View/Scene.hpp"
#include "View/View.hpp"

#include <iostream>

namespace RG {
    namespace View {
        //! \class GameScene
        /*!
         *  \brief GameScene ( descedant of Scene ) 
         *  This scene where is main menu of the game
         */
        class MenuScene : public Scene {
        public:
            //! A constructor
            MenuScene();

            //! A destructor
            virtual ~MenuScene();

            //! Update menu scene
            /*!
             * \param view pinter to game View
             * \param timeElapsed time alapsed from last update
             */
            virtual void Update(View *view, float timeElapsed);

            //! Render menu scene
            /*!
             * \param view pinter to game View
             */
            virtual void Render(View *view);

            //! Manage player input
            /*!
             * \param view pinter to game View
             */
            virtual void ManageInput(View *view);

        private:
            const float m_itemWidth = 100;
            const float m_itemHeight = 50;
            const float m_menuWidth = m_itemWidth + 20;
            const float m_menuHeight = m_itemHeight * 4 + 30;
            bool m_showSetting;
            bool m_showMenu;
            bool m_notReset;
            float m_settingsWidth = 400;
            float m_settingsHeight = 300;

            sf::Texture background_texture;
            sf::Sprite background;
            float windowX;
            float windowY;
        };
    }
}
