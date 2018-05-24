#pragma once

#include <SFML/Graphics.hpp>
#include <sol.hpp>

#include "Model/Floor.hpp"
#include "Model/Model.hpp"
#include "RoomHistory.hpp"
#include "View/Animation.hpp"
#include "View/Entity.hpp"
#include "Util/Observer.hpp"

namespace RG{
    namespace View{
        class GameScene;
        class Room : RoomHistory, public sf::Drawable, public Util::Observer{
        public:
            Room(GameScene * scene, sol::state & lua, Model::Model * model);
            ~Room();
            void ChangeRoom(Model::Floor * floor);
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
            void SetDoors(std::vector<bool> doors);
            void Update(View * view, float timeElapsed);
            virtual void onNotify(Util::Subject * subject, Util::Event event) override;
        protected:
        private:
            void SetScale(float,float);
            sol::state m_lua;
            void SetDoorScaleLeftRight(float x, float y);
            void SetDoorScaleTopBot(float x, float y);

            int currentId;
            void AssignBackground(int level, int id);
            void SetDoorPosition();
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

            std::vector<Entity> enemies;
            GameScene * m_gameScene;
            Model::Model * m_model;
        };
    }
}
