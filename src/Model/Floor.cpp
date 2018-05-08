#include "Model/Floor.hpp"

#ifdef DEBUG_DRAW
sf::RenderWindow m_window(sf::VideoMode(800, 600), "Debug Draw",
    sf::Style::Default, sf::ContextSettings{ 0u, 0u, 4u, 1u, 1u, 0u, false });
DebugDraw debugDraw(&m_window);
#endif //DEBUG_DRAW

namespace RG {
  namespace Model {
    Floor::Floor(unsigned int level, unsigned int rooms, unsigned int pos_X,
        unsigned int pos_Y)
      : m_X(pos_X)
        , m_Y(pos_Y)
        , m_Level(level)
        , m_ScreenHeight(1080)
        , m_ScreenWidth(1920)
        , center_x(-16000)
        , center_y(-16000)
        , size(100000)
    {
      m_World = std::make_shared<b2World>(b2Vec2{ 0.0f, 0.0f });

      /*
      m_World->SetDebugDraw(&debugDraw);
      debugDraw.SetFlags(b2Draw::e_shapeBit);
      view.reset(sf::FloatRect(center_x, center_y, size, size));

      m_window.setView(view);
      */

      m_WallWidth = 0.076389 * m_ScreenWidth;
      m_WallHeight = 0.1267 * m_ScreenHeight;
      m_DoorWidth = 0.05 * m_ScreenWidth;
      m_RoomHeight = m_ScreenHeight - 2 * m_WallHeight + 30;
      m_RoomWidth = m_ScreenWidth - 2 * m_WallWidth + 20;

      for (unsigned int i = 0; i < rooms; ++i) {
        RG::Model::Room* tmp_room = new RG::Model::Room(0, i);
        b2BodyDef* room_bodyDef = new b2BodyDef;
        room_bodyDef->type = b2_dynamicBody;
        room_bodyDef->position.Set(0 * m_RoomWidth, i * m_RoomHeight);
        tmp_room->m_Body = m_World->CreateBody(room_bodyDef);

        tmp_room->SetDoors({ !!(i % 2), 0, !(i % 2), 0 }); // FIXME (vanda)
        tmp_room->AddWalls(m_ScreenWidth, m_ScreenHeight, m_DoorWidth,
            m_WallWidth, m_WallHeight);

        auto it1 = m_Rooms.find(0);
        if (it1 == m_Rooms.end()) {
          m_Rooms.insert({ 0, { { i, tmp_room } } });
        } else {
          it1->second.insert({ i, tmp_room });
        }
      }
    }

    Floor::~Floor() {}

    unsigned int Floor::GetLevel(void) const { return m_Level; }

    const RG::Model::Room& Floor::GetRoom(void) const
    {
      auto it_row = m_Rooms.find(m_X);
      if (it_row == m_Rooms.end()) {
        RG::Model::Room* tmp = new RG::Model::Room(0, 0);
        return *tmp;
      }
      auto it_col = it_row->second.find(m_Y);
      if (it_col == it_row->second.end()) {
        RG::Model::Room* tmp = new RG::Model::Room(0, 0);
        return *tmp;
      }
      return *(it_col->second);
    }

    b2Body* Floor::GetPlayerBody(b2BodyDef* bodyDef)
    {
      return m_World->CreateBody(bodyDef);
    }

    void Floor::Step(float time_step)
    {
      this->m_World->Step(time_step, 8, 3);
      this->m_World->ClearForces();
#ifdef DEBUG_DRAW
      m_window.clear({ 0, 0, 0, 255 });
      sf::Event event;
      while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
          if (event.key.code == sf::Keyboard::Left) {
            center_x += 1000;
          }
          if (event.key.code == sf::Keyboard::Right) {
            center_x -= 1000;
          }
          if (event.key.code == sf::Keyboard::Down) {
            center_y -= 1000;
          }
          if (event.key.code == sf::Keyboard::Up) {
            center_y += 1000;
          }
          if (event.key.code == sf::Keyboard::Add) {
            size *= 1.5;
          }
          if (event.key.code == sf::Keyboard::Subtract) {
            size /= 1.5;
          }
        }
      }
      view.setCenter(center_x, center_y);
      view.setSize(size, size);
      m_window.setView(view);
      m_World->DrawDebugData();
      m_window.display();
#endif //DEBUG_DRAW
    }

    void Floor::UpdateID(b2Vec2 v)
    {
      m_X = (v.x - m_WallWidth) / m_RoomWidth;
      m_Y = (v.y - m_WallHeight) / m_RoomHeight;
    }
  }
}
