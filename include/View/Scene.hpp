#pragma once

namespace RG {
    namespace View {
        class View;

        //! \class Scene
        /*!
         *  \brief Scene class
         *  Abstract ancestor af all game scenes
         */
        class Scene {
        public:
            //! A constructor
            Scene();

            //! A destructor
            virtual ~Scene();

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

            //! Manege player input
            /*!
             * \param view pinter to game View
             */
            virtual void ManageInput(View *view);
        };
    }
}
