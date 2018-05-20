#pragma once

#include <map>
#include <string>

#include "Model/ContactListener.hpp"
#include "Model/Object.hpp"
#include "Model/Room.hpp"
#include "Util/Event.hpp"
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
        /// constructor
        Floor(unsigned int level, unsigned int rooms, unsigned int pos_X,
            unsigned int pos_Y);

        /// destructor
        virtual ~Floor();

        /// returns how many floors under ground this floor is
        unsigned int GetLevel(void) const;

        const RG::Model::Room& GetRoom(void) const;

        /// adds player to the world and returns box2d body
        b2Body* GetPlayerBody(b2BodyDef* bodyDef);

        void Step(float time_step, b2Vec2 PlayerPos);

        void UpdateID(b2Vec2 v);

        unsigned int m_X;
        unsigned int m_Y;

        unsigned int m_RoomHeight;
        unsigned int m_RoomWidth;

      private:
        RG::Model::Room& __GetRoom(void) const;

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
