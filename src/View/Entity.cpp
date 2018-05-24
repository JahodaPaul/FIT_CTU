#include "View/Entity.hpp"
#include "View/View.hpp"
#include "View/GameScene.hpp"

namespace RG{
    namespace View {
        Entity::Entity(GameScene * gameScene) :
            correctionX( 0 )
            ,correctionY( 0 )
            ,m_moved{ false }
            ,windowX{0}
            ,windowY{0}
            ,time{0}
        {
            animation = std::make_shared<Animation>("/usr/share/RG/assets/graphics/objects/characters/zombie.png", 100, 87, 8, 40.0f);
            gameScene->AddObserver( this );
            animation->setPosition(sf::Vector2f(this->x, this->y));
            animation->goToFrame(0);
            animation->startAnimation();
        }

        Entity::~Entity() {}

        void Entity::SetPosition(float x, float y) {
            this->x = x;
            this->y = y;
            animation->setPosition({x*(windowX/1920), y*(windowY/1080)});
        }

        void Entity::Update(View * view, float timeElapsed) {
            if (m_moved) {
                this->animation->update(timeElapsed);
                m_moved = false;
            }
        }

        void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            target.draw( *animation );
        }

        void Entity::SetScale(float windowWidth, float windowHeight){
            if(windowWidth != windowX || windowHeight != windowY) {
                float scaleX = (windowWidth / 20) / this->animation->getSize().x;
                float scaleY = (windowWidth / 20) / this->animation->getSize().x;
                this->animation->setScale(scaleX, scaleY);
                windowX = windowWidth;
                windowY = windowHeight;
            }
        }

        void RG::View::Entity::onNotify(const Util::Subject * subject, Util::Event event) {
            switch(event) {
                case Util::Event::ENTITY_MOVE:
                    {
                        Model::Entity * entity = (Model::Entity*)subject;
                        float absoluteX = entity->GetPosition().x - correctionX;
                        float absoluteY = entity->GetPosition().y - correctionY;
                        this->animation->setRotation(entity->GetAngle() * 180 / M_PI + 90);
                        this->SetPosition(absoluteX,absoluteY);
                        m_moved = true;
                        break;
                    }
                case Util::Event::ROOM_CHANGE:
                    {
                        Model::Floor * floor = (Model::Floor*)subject;
                        correctionX = floor->m_X * floor->m_RoomWidth;
                        correctionY = floor->m_Y * floor->m_RoomHeight;
                        break;
                    }
                case Util::Event::WINDOW_RESIZE:
                    {
                        GameScene * gameScene = (GameScene*)subject;
                        SetScale( gameScene->getWindowSize().x, gameScene->getWindowSize().y );
                        break;
                    }
                default:
                    break;
            }       
        }
    }
}
