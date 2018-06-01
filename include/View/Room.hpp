#pragma once

#include <memory>
#include <tuple>

#include <SFML/Graphics.hpp>
#include <sol.hpp>

#include "Model/Floor.hpp"
#include "Model/Model.hpp"
#include "Model/Stairs.hpp"

#include "RoomHistory.hpp"
#include "View/Animation.hpp"
#include "View/Entity.hpp"
#include "Util/Observer.hpp"

namespace RG{
    namespace View{
        class GameScene;
        /**
         * \class Room
         * \brief Presentation a room used to draw room, player, enemies...
         */
        class Room : RoomHistory, public sf::Drawable, public Util::Observer{
        public:
            //! Room class constructor.
            /*!
             * Method takes three parameters:
             *
             * @param scene pointer to GameScene
             * @param lua pointer to lua state
             * @param model pointer to Model used for registering Observers
             */
            Room(GameScene * scene, sol::state & lua, Model::Model * model);

            virtual ~Room();

            /// assigns background image if the room has never been visited
            /// if it has been visited - changes background image based on room ID
            /// receives from model which doors to draw
            void ChangeRoom(Model::Floor * floor);

            /*!
             * Draws room and everything in it.
             */
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;

            ///Sets which doors are visible
            void SetDoors(std::vector<bool> doors);

            /*!
             * Updates room and everytinkg in it.
             *
             * @param view pointer to View
             * @param timeElapsed time elapsed since last update
             */
            void Update(View * view, float timeElapsed);

            /*!
             * This methos is used to recieve nitifikations from model
             */
            virtual void onNotify(Util::Subject * subject, Util::Event event) override;
        protected:
        private:
            void SetScale(float,float);
            void SetDoorScaleLeftRight(float x, float y);
            void SetDoorScaleTopBot(float x, float y);
            ///assign background image to new room
            void AssignBackground(int level, int id);
            void SetDoorPosition();
            void SetStairs( std::vector<std::shared_ptr<RG::Model::Stairs> > );

        private:
            sol::state & m_lua;

            int currentId;
            sf::Texture room_texure;
            sf::Sprite background;

            float windowX;
            float windowY;

            float winDoorsX;
            float winDoorsY;

            struct {
                sf::Sprite sprite;
                sf::Texture texture;
                bool visible;
            } doors[4];

            const std::string room_bluestone;
            const std::string room_blackstone;
            const std::string room_cobblestone;
            const std::string room_soil;
            const std::string room_lava;

            float m_correctionX;
            float m_correctionY;

            std::vector<std::unique_ptr<Entity>> enemies;
            GameScene * m_gameScene;
            Model::Model * m_model;

            std::pair<bool,Entity> m_stairs[2];
        };
    }
}
