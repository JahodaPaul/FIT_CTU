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
            ,m_stairs{ {false, {gameScene, lua, "stairs_up"}}, {false, {gameScene, lua, "stairs_down"}} }
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

                SubscribeTo( gameScene );
                SubscribeTo( &model->GetCurrentFloor() );
                SubscribeTo( model );

                m_stairs[0].second.SubscribeTo( &model->GetCurrentFloor() );
                m_stairs[1].second.SubscribeTo( &model->GetCurrentFloor() );
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
            m_correctionX = floor->m_X * floor->m_RoomWidth;
            m_correctionY = floor->m_Y * floor->m_RoomHeight;

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
            SetStairs( floor->GetRoom().GetStairs() );

            auto it = this->roomHistory.find(std::to_string(id));
            room_texure.loadFromFile(it->second);
            background.setTexture(room_texure);

            enemies.clear();
            for ( auto it : floor->GetRoom().GetEntities() ) {
                enemies.push_back(std::make_unique<Entity>(m_gameScene, m_lua, "zombie", it->GetWidth(), it->GetHeight() ));
                enemies.back()->setCorrection( m_correctionX, m_correctionY );
                enemies.back()->SubscribeTo( &(*it) );
                enemies.back()->SubscribeTo( &(*floor) );
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
            float scaleX = (x / 7) / doors[0].sprite.getLocalBounds().width;
            doors[0].sprite.setScale(scaleX,scaleY);
            doors[2].sprite.setScale(scaleX,scaleY);
        }

        void Room::SetDoorScaleLeftRight(float x, float y){
            float scaleY = (float)(y / 3.5) / doors[1].sprite.getLocalBounds().height;
            float scaleX = (x / 12) / doors[1].sprite.getLocalBounds().width;
            doors[1].sprite.setScale(scaleX,scaleY);
            doors[3].sprite.setScale(scaleX,scaleY);
        }

        void Room::Update(View * view, float timeElapsed) {
            for ( size_t i = 0; i<enemies.size(); ++i ) {
                if ( enemies[i]->Alive() )
                    enemies[i]->Update( view, timeElapsed );
                else {
                    enemies.erase( enemies.begin() + i-- );
                }
            }
        }

        void Room::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            target.draw(background);
            for ( auto i = 0; i < 4; ++i )
                if ( doors[i].visible ) target.draw( doors[i].sprite );
            for ( auto i = 0; i < 2; ++i )
                if ( m_stairs[i].first ) target.draw( m_stairs[i].second );
            for ( auto & it : enemies )
                target.draw( *it );
        }

        void Room::SetStairs( std::vector<std::shared_ptr<RG::Model::Stairs> > stairs ) {
            m_stairs[0].second.setCorrection( m_correctionX, m_correctionY );
            m_stairs[1].second.setCorrection( m_correctionX, m_correctionY );

            m_stairs[0].first = false;
            m_stairs[1].first = false;

            for ( unsigned int i = 0;i<stairs.size();++i ) {
                if ( stairs[i] != nullptr ) {
                    m_stairs[i].first = true;
                    m_stairs[i].second.SetPosition( stairs[i]->GetPosition().x - m_correctionX, stairs[i]->GetPosition().y - m_correctionY );
                }
            }
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
                case Util::Event::FLOOR_CHANGE:
                    {
                        Model::Floor * floor = &((Model::Model*)subject)->GetCurrentFloor();
                        SubscribeTo( floor );
                        m_gameScene->getPlayer().get()->SubscribeTo( floor );
                        ChangeRoom( floor );
                        break;
                    }
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
