#include "View/Entity.hpp"
#include "View/View.hpp"
#include "View/GameScene.hpp"

namespace RG{
    namespace View {
        Entity::Entity(GameScene * gameScene, sol::state & luaState, std::string name, float sizeX, float sizeY) :
            correctionX{ 0 }
            ,correctionY{ 0 }
            ,m_moved{ false }
            ,time{0}
            ,m_rotationCorrection{0}
            ,sizeX{ sizeX }
            ,sizeY{ sizeY }
            ,m_alive{ true }
            ,m_lua{ &luaState }
            ,m_name{ name }
        {
            m_roomSizeX = gameScene->getModel()->GetRoomWidth();
            m_roomSizeY = gameScene->getModel()->GetRoomHeight();
            windowX = gameScene->getViewSize().x; 
            windowY = gameScene->getViewSize().y;
            if ( !luaState[name] )
                name = "default";
            std::string texture = luaState[name]["textureFile"];
            int frameWidth = luaState[name]["frameWidth"];
            int frameHeight = luaState[name]["frameHeight"];
            int frameCount = luaState[name]["frameCount"];
            float frameTime = luaState[name]["frameTime"];
            m_rotationCorrection = luaState[name]["rotation"];
            m_rotationCorrection += 90;
            animation = std::make_shared<Animation>(texture.c_str(), frameWidth, frameHeight, frameCount, frameTime);
            SubscribeTo( gameScene );
            animation->setPosition(sf::Vector2f(this->x, this->y));
            animation->setRotation(m_rotationCorrection);
            animation->goToFrame(0);
            animation->startAnimation();
            SetScale( windowX, windowY );
        }

        Entity::~Entity() {}

        void Entity::setCorrection( float correctionX, float correctionY ) {
            this->correctionX = correctionX;
            this->correctionY = correctionY;
        }

        void Entity::SetPosition(float x, float y) {
            this->x = x;
            this->y = y;
            animation->setPosition({x*(windowX/m_roomSizeX), y*(windowY/m_roomSizeY)});
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
                float scaleX =  ( (float)windowWidth / m_roomSizeX ) / (float)( animation->getSize().x / sizeX );
                float scaleY = ( (float)windowHeight / m_roomSizeY ) / (float)( animation->getSize().y / sizeY );
                animation->setScale(scaleX, scaleY);
                windowX = windowWidth;
                windowY = windowHeight;
        }

        bool Entity::Alive() const {
            return m_alive;
        }

        void RG::View::Entity::onNotify(Util::Subject * subject, Util::Event event) {
            switch(event) {
                case Util::Event::ENTITY_MOVE:
                    {
                        Model::Entity * entity = (Model::Entity*)subject;
                        float absoluteX = entity->GetPosition().x - correctionX;
                        float absoluteY = entity->GetPosition().y - correctionY;
                        this->animation->setRotation(entity->GetAngle() * 180.0f / M_PI + m_rotationCorrection);
                        this->SetPosition(absoluteX,absoluteY);
                        m_moved = true;
                        break;
                    }
                case Util::Event::FLOOR_CHANGE:
                    {
                        Model::Floor * floor = &((Model::Model*)subject)->GetCurrentFloor();
                        correctionX = floor->m_X * floor->m_RoomWidth;
                        correctionY = floor->m_Y * floor->m_RoomHeight;
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
                        SetScale( gameScene->getViewSize().x, gameScene->getViewSize().y );
                        break;
                    }
                case Util::Event::SHOT_CRASHED:
                    {
                        m_alive = false;
                        break;
                    }
                case Util::Event::ENTITY_DEAD:
                    {
                        subject->RemoveObserver( this );
                        m_alive = false;
                        (*m_lua)[m_name]["Dead"]();
                        break;
                    }
                case Util::Event::ENTITY_DAMAGED:
                    {
                        (*m_lua)[m_name]["Hurt"]();
                        break;
                    }
                default:
                    break;
            }       
        }
    }
}
