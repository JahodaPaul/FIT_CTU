#pragma once

#include "View/Scene.hpp"
#include "View/View.hpp"

#include "View/Player.hpp"
#include "View/Entity.hpp"
#include "View/Room.hpp"
#include "Util/Subject.hpp"

#include <iostream>

namespace RG {
    namespace View {
        //! \class GameScene
        /*!
         *  \brief ( descendant of Scene ) 
         *  This scene where gameplay takes place
         */
        class GameScene : public Scene, public Util::Subject {
        public:
            //! A constructor
            GameScene(View *view);

            //! A destructor
            virtual ~GameScene();

            //! Update game scene
            /*!
             * \param view pointer to game View
             * \param timeElapsed time elapsed from last update
             */
            virtual void Update(View *view, float timeElapsed);

            //! Render game scene
            /*!
             * \param view pointer to game View
             */
            virtual void Render(View *view);

            //! Manage player input
            /*!
             * \param view pointer to game View
             */
            virtual void ManageInput(View *view);

            const sf::Vector2f & getWindowSize() const;
        private:
            std::shared_ptr<RG::View::Player> GetPlayer();
            sf::Vector2f m_windowSize;

            void SetPlayer();

            void DrawRoom(View *view);

            std::shared_ptr<Entity> test_zombie;

            std::shared_ptr<RG::View::Player> player;
            std::shared_ptr<RG::View::Room> room;
            bool m_firstFrame;
        };
    }
}
