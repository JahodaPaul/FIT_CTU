#pragma once

#include <map>
#include <string>

#include "Model/ContactListener.hpp"
#include "Model/Object.hpp"
#include "Model/Room.hpp"
#include "Model/Stairs.hpp"
#include "Util/Event.hpp"
#include "Util/Observer.hpp"
#include "Util/Subject.hpp"

#ifdef DEBUG_DRAW

#include "View/DebugDraw.hpp"
#include <SFML/Window.hpp>

extern sf::RenderWindow m_window;
extern RG::View::DebugDraw debugDraw;

#endif // DEBUG_DRAW

namespace RG {
  namespace Model {
    /**
     * \class Floor
     * \brief This class desribes a floor inside the game world. There are
     * multiple rooms inside and the transition between floors is by stairs.
     */
    class Floor : public Util::Subject {
      public:
        /**
         * \function Floor
         * \brief constructor
         * @param level how deep under ground the floor is
         * @param rooms how many rooms are there going to be
         * @param pos_X horizontal postition(in the rooms grid) of the room where
         * the player starts in this floor
         * @param pos_Y vertical postition(in the rooms grid) of the room where the
         * player starts in this floor
         * @param MAX_FLOORS total number of floors in the game
         */
        Floor(unsigned int level, unsigned int rooms, unsigned int pos_X,
            unsigned int pos_Y, unsigned int MAX_FLOORS);

        /**
         * \function ~Floor
         * \brief destructor
         */
        virtual ~Floor();

        /**
         * \function GetRoom
         * \brief returns how many floors under ground this floor is
         */
        unsigned int GetLevel(void) const;

        /**
         * \function GetRoom
         * \brief returns a const reference to the current floor
         */
        const RG::Model::Room& GetRoom(void) const;

        /**
         * \function GetPlayerBody
         * \brief adds player to the world and returns a box2d body
         * @param bodyDef Box2D body definition, should be complete and ready
         * for adding into the Box2D world
         */
        b2Body* GetPlayerBody(b2BodyDef* bodyDef);

        /**
         * \function Step
         * \brief advances time in the physical world, checks for dead bodies
         * and makes entitities in the current room move
         * @param time_step how much time has elapsed since last Step
         * @param PlayerPos player's current position
         */
        void Step(float time_step, b2Vec2 PlayerPos);

        /**
         * \function UpdateID
         * \brief calculates Room ID and sends a notification if it changes
         * @param v player's current position
         */
        void UpdateID(b2Vec2 v);

        /**
         * \function GetRoomId
         * \brief returns the current Room ID
         */
        unsigned int GetRoomId(void) const;

        void AddStairsObserver(RG::Util::Observer* obs);

        unsigned int m_X;
        unsigned int m_Y;

        unsigned int m_RoomHeight;
        unsigned int m_RoomWidth;

      private:
        /**
         * \function __GetRoom
         * \brief returns a (NOT const) reference to the current floor
         */
        RG::Model::Room& __GetRoom(void) const;

        /**
         * \function __GenerateRooms
         * \brief randomly generates room layout, expects m_Rooms to be clear
         * @param cnt how many rooms will be generated
         */
        void __GenerateRooms(unsigned int cnt);

        /// array of rooms present at this floor
        std::map<unsigned int, std::map<unsigned int, RG::Model::Room*>> m_Rooms;

        /// how deep under ground the floor is
        unsigned int m_Level;

        /// title of the floor
        std::string m_Title;

        /// box2d world, where all objects will be placed
        std::shared_ptr<b2World> m_World;

        unsigned int m_ScreenHeight;
        unsigned int m_ScreenWidth;

        unsigned int m_WallWidth;
        unsigned int m_WallHeight;
        unsigned int m_DoorWidth;

        RG::Model::ContactListener* m_ContactListener;
#ifdef DEBUG_DRAW
        sf::View view;
#endif // DEBUG_DRAW
        int center_x, center_y;
        float size;
    };
  }
}
