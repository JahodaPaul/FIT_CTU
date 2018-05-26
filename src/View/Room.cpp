#include "View/Room.hpp"
#include "View/GameScene.hpp"

namespace RG {
    namespace View {

        RG::View::Room::Room(GameScene * gameScene, sol::state & lua, Model::Model * model) :
            m_lua( lua )
            ,room_bluestone("/usr/share/RG/assets/graphics/backgrounds/rooms/BlueStoneBG.png")
            ,room_blackstone("/usr/share/RG/assets/graphics/backgrounds/rooms/BlackStoneBG.png")
            ,room_cobblestone("/usr/share/RG/assets/graphics/backgrounds/rooms/CobbleStoneBG.png")
            ,room_soil("/usr/share/RG/assets/graphics/backgrounds/rooms/SoilBG.png")
            ,room_lava("/usr/share/RG/assets/graphics/backgrounds/rooms/LavaBG.png")
            ,m_gameScene( gameScene )
            ,m_model( model )
            {
                windowX = gameScene->getWindowSize().x;
                windowY = gameScene->getWindowSize().y;
                currentId = -1;
                doors[0].texture.loadFromFile("/usr/share/RG/assets/graphics/objects/doors/door-top.png");
                doors[1].texture.loadFromFile("/usr/share/RG/assets/graphics/objects/doors/door-right.png");
                doors[2].texture.loadFromFile("/usr/share/RG/assets/graphics/objects/doors/door-bottom.png");
                doors[3].texture.loadFromFile("/usr/share/RG/assets/graphics/objects/doors/door-left.png"); 

                doors[0].sprite.setTexture(doors[0].texture);
                doors[1].sprite.setTexture(doors[1].texture);
                doors[2].sprite.setTexture(doors[2].texture);
                doors[3].sprite.setTexture(doors[3].texture);
                doors[0].visible = false;
                doors[1].visible = false;
                doors[2].visible = false;
                doors[3].visible = false;

                gameScene->AddObserver( this );
                model->GetCurrentFloor().AddObserver( this );
            }

        RG::View::Room::~Room() {

        }

        void RG::View::Room::AssignBackground(int level, int id) {
            std::string first;
            std::string second;
            if(level == 0){
                first = room_bluestone;
                second = room_blackstone;
            }
            else if(level == 1){
                first = room_blackstone;
                second = room_cobblestone;
            }
            else if(level == 2){
                first = room_cobblestone;
                second = room_soil;
            }
            else{
                first = room_soil;
                second = room_lava;
            }

            this->currentId = id;
            if(std::rand() % 2 == 0){
                this->roomHistory.insert(std::make_pair(std::to_string(id),first));
            }
            else{
                this->roomHistory.insert(std::make_pair(std::to_string(id),second));
            }
        }

        void RG::View::Room::ChangeRoom(Model::Floor * floor) {
            SetScale( windowX, windowY );
            int level = floor->GetLevel();
            int id = floor->GetRoomId();
            if(id == this->currentId)
                return;

            if(this->roomHistory.find(std::to_string(id)) == this->roomHistory.end()){
                this->AssignBackground(level,id);
            }
            else{
                this->currentId = id;
            }

            SetDoors( floor->GetRoom().GetDoors() );

            auto it = this->roomHistory.find(std::to_string(id));
            room_texure.loadFromFile(it->second);
            background.setTexture(room_texure);

            //TODO(vojta) remove listenres
            enemies.clear();
            float correctionX = floor->m_X * floor->m_RoomWidth;
            float correctionY = floor->m_Y * floor->m_RoomHeight;
            for ( auto it : floor->GetRoom().GetEntities() ) {
                enemies.emplace_back(m_gameScene, m_lua, "zombie" );
                enemies.back().setCorrection( correctionX, correctionY );
                it->AddObserver( &enemies.back() );
                floor->AddObserver( &enemies.back() );
            }
        }

        void Room::SetDoorPosition(){
            doors[0].sprite.setPosition({(windowX/2)-(doors[0].sprite.getLocalBounds().width * doors[0].sprite.getScale().x/2)
                    ,0});
            doors[1].sprite.setPosition({windowX-(doors[1].sprite.getLocalBounds().width * doors[1].sprite.getScale().x)
                    ,(windowY/2)-(doors[1].sprite.getLocalBounds().height* doors[1].sprite.getScale().y/2)});
            doors[2].sprite.setPosition({(windowX/2)-(doors[2].sprite.getLocalBounds().width* doors[2].sprite.getScale().x/2)
                    ,windowY-(doors[2].sprite.getLocalBounds().height*doors[2].sprite.getScale().y)});
            doors[3].sprite.setPosition({0
                    ,(windowY/2)-(doors[3].sprite.getLocalBounds().height* doors[3].sprite.getScale().y/2)});
        }

        void Room::SetScale(float x, float y) {
            windowX = x;
            windowY = y;

            SetDoorPosition();
            background.setScale(x / background.getLocalBounds().width, y / background.getLocalBounds().height);
            SetDoorScaleTopBot(x,y);
            SetDoorScaleLeftRight(x,y);
        }

        void Room::SetDoorScaleTopBot(float x, float y){
            float scaleY = (float)(y / 7.5) / doors[0].sprite.getLocalBounds().height;
            doors[0].sprite.setScale(scaleY,scaleY);
            doors[2].sprite.setScale(scaleY,scaleY);
        }

        void Room::SetDoorScaleLeftRight(float x, float y){
            float scaleX = (x / 12) / doors[1].sprite.getLocalBounds().width;
            doors[1].sprite.setScale(scaleX,scaleX);
            doors[3].sprite.setScale(scaleX,scaleX);
        }

        void Room::Update(View * view, float timeElapsed) {
            for ( size_t i = 0; i<enemies.size(); ++i ) {
                if ( enemies[i].Alive() )
                    enemies[i].Update( view, timeElapsed );
                else {
                    m_gameScene->RemoveObserver( &enemies[i] );
                    m_model->GetCurrentFloor().RemoveObserver( &enemies[i] );
                    enemies.erase( enemies.begin() + i-- );
                }
            }
        }

        void Room::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            target.draw(background);
            for ( auto i = 0; i < 4; ++i )
                if ( doors[i].visible ) target.draw( doors[i].sprite );
            for ( auto & it : enemies )
                target.draw( it );
        }

        void Room::SetDoors(std::vector<bool> doors) {
            unsigned int i = 0;
            for ( ;i<doors.size();++i ) {
                this->doors[i].visible = doors[i];
            }
            for ( ;i<4;++i ) {
                this->doors[i].visible = false;
            }
        }

        void RG::View::Room::onNotify(Util::Subject * subject, Util::Event event) {
            switch(event) {
                case Util::Event::ROOM_CHANGE:
                    {
                        Model::Floor * floor = (Model::Floor*)subject;
                        ChangeRoom( floor );
                        break;
                    }
                case Util::Event::WINDOW_RESIZE:
                    {
                        GameScene * gameScene = (GameScene*)subject;
                        float x = gameScene->getWindowSize().x;
                        float y = gameScene->getWindowSize().y;
                        SetScale( x, y );
                        break;
                    }
                default:
                    break;
            }       
        }
    }
}
