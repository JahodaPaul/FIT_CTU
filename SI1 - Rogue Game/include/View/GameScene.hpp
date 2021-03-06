#pragma once

#include "View/Scene.hpp"
#include "View/View.hpp"
#include "View/Player.hpp"
#include "View/Entity.hpp"
#include "View/Room.hpp"
#include "Util/Subject.hpp"
#include "View/SoundManager.hpp"
#include "View/NPCLog.hpp"
#include "View/Gui.hpp"

#include "Model/Model.hpp"

#include <iostream>

namespace RG {
    namespace View {
        /*!
         * \class GameScene
         *
         * \brief ( descendant of Scene ) This scene where gameplay takes place
         */
        class GameScene : public Scene, public Util::Subject {
        public:
            /*!
             * \brief A constructor
             *
             * @param view pointer to View
             */
            GameScene(View *view);

            /*!
             * \brief A destructor
             */
            virtual ~GameScene();

            /*!
             * Update game scene
             * @param view pointer to game View
             * @param timeElapsed time elapsed from last update
             */
            virtual void Update(View *view, float timeElapsed);

            /*!
             * \brief Render game scene.
             *
             * @param view pointer to game View
             */
            virtual void Render(View *view);

            /*!
             * \brief Manage player input.
             *
             * @param view pointer to game View
             */
            virtual void ManageInput(View *view);

            /*!
             * \brief Get shared pointer to Player.
             */
            std::shared_ptr<Player> getPlayer();

            /*!
             * \brief Get game view size.
             */
            const sf::Vector2f & getViewSize() const;

            /*!
             * \brief Get game window size.
             */
            const sf::Vector2u & getWindowSize() const;

            /*!
             * \brief Get pointer to game Model.
             */
            RG::Model::Model * getModel();
        private:
            sf::Vector2f m_viewSize;
            sf::Vector2u m_windowSize;

            void SetPlayer();

            std::shared_ptr<RG::View::Player> player;
            std::shared_ptr<RG::View::Room> room;
            NPCLog m_npcLog;
            RG::View::Gui m_gui;
            RG::Model::Model * m_model;
        };
    }
}
