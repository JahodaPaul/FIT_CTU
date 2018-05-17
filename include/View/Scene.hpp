#pragma once

namespace RG {
    namespace View {
        class View;

        //! \class Scene
        /*!
         *  \brief
         *  This is abstract ancestor of all game scenes
         */
        class Scene {
        public:
            //! A constructor
            Scene();

            //! A destructor
            virtual ~Scene();

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

            //! Manege player input
            /*!
             * \param view pointer to game View
             */
            virtual void ManageInput(View *view);
        };
    }
}
