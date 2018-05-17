#pragma once

#include "View/Scene.hpp"
#include "View/View.hpp"

#include "View/Player.hpp"
#include "View/Room.hpp"

#include <iostream>

namespace RG {
    namespace View {
        //! \class GameScene
        /*!
         *  \brief GameScene ( descedant of Scene ) 
         *  This scene where gameplay takes place
         */
        class GameScene : public Scene {
        public:
            //! A constructor
            GameScene();

            //! A destructor
            virtual ~GameScene();

            //! Update game scene
            /*!
             * \param view pinter to game View
             * \param timeElapsed time alapsed from last update
             */
            virtual void Update(View *view, float timeElapsed);

            //! Render game scene
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
            std::shared_ptr<RG::View::Player> GetPlayer();

            void SetPlayer();

            void SetPlayerSpeedY(float);

            void SetPlayerSpeedX(float);

            float GetPlayerSpeedY();

            float GetPlayerSpeedX();

            void UpdatePlayer(View * view, float timeElapsed);

            void DrawPlayer(View *view);

            void DrawRoom(View *view);


            std::shared_ptr<RG::View::Player> player;
            std::shared_ptr<RG::View::Room> room;
        };
    }
}
