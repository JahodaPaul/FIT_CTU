#include "Model/Floor.hpp"

#ifdef DEBUG_DRAW
sf::RenderWindow m_window(sf::VideoMode(800, 600), "Debug Draw",
    sf::Style::Default, sf::ContextSettings{ 0u, 0u, 4u, 1u, 1u, 0u, false });
RG::View::DebugDraw debugDraw(&m_window);
#endif // DEBUG_DRAW

namespace RG {
  namespace Model {
    Floor::Floor(unsigned int level, unsigned int rooms, unsigned int pos_X,
        unsigned int pos_Y, unsigned int MAX_FLOORS, unsigned int screen_h,
        unsigned int screen_w)
      : m_X(pos_X)
        , m_Y(pos_Y)
        , m_Level(level)
        , m_ScreenHeight(screen_h)
        , m_ScreenWidth(screen_w)
        , center_x(-1600)
        , center_y(-1600)
        , size(10000)
    {
      m_World = std::make_shared<b2World>(b2Vec2{ 0.0f, 0.0f });

#ifdef DEBUG_DRAW
      m_World->SetDebugDraw(&debugDraw);
      debugDraw.SetFlags(b2Draw::e_shapeBit);
      view.reset(sf::FloatRect(center_x, center_y, size, size));

      m_window.setView(view);
#endif // DEBUG_DRAW

      m_WallWidth = 0.076389 * m_ScreenWidth;
      m_WallHeight = 0.1267 * m_ScreenHeight;
      m_DoorWidth = 0.05 * m_ScreenWidth;
      m_RoomHeight = m_ScreenHeight - 2 * m_WallHeight + 3;
      m_RoomWidth = m_ScreenWidth - 2 * m_WallWidth + 2;

      m_Stairs = __GenerateRooms(rooms);

      mainLog.Info("(" + std::to_string(m_Stairs.first.first) + ","
          + std::to_string(m_Stairs.first.second) + "), ("
          + std::to_string(m_Stairs.second.first) + " "
          + std::to_string(m_Stairs.second.second) + ")");

      if (level > 0) {
        __GetRoom(m_Stairs.first.first, m_Stairs.first.second)
          .AddStairs(true, m_World, m_RoomWidth, m_RoomHeight);
      }

      if (level < MAX_FLOORS - 1) {
        __GetRoom(m_Stairs.second.first, m_Stairs.second.second)
          .AddStairs(false, m_World, m_RoomWidth, m_RoomHeight);
      }

      m_ContactListener = new ContactListener(m_World);
    }

    Floor::~Floor()
    {
      delete m_ContactListener;
      for (auto i : m_Rooms) {
        for (auto j : i.second) {
          delete j.second;
        }
      }
    }

    unsigned int Floor::GetLevel(void) const { return m_Level; }

    const RG::Model::Room& Floor::GetRoom(void) const { return __GetRoom(); }

    RG::Model::Room& Floor::__GetRoom(unsigned int x, unsigned int y) const
    {
      auto it_row = m_Rooms.find(x);
      if (it_row == m_Rooms.end()) {
        throw RG::Model::RoomNotFound();
      }
      auto it_col = it_row->second.find(y);
      if (it_col == it_row->second.end()) {
        throw RG::Model::RoomNotFound();
      }
      return *(it_col->second);
    }

    RG::Model::Room& Floor::__GetRoom(void) const { return __GetRoom(m_X, m_Y); }

    b2Body* Floor::GetPlayerBody(b2BodyDef* bodyDef)
    {
      return m_World->CreateBody(bodyDef);
    }

    void Floor::Step(float time_step, b2Vec2 PlayerPos)
    {
      // clearing dead bodies
      b2Body* _b = this->m_World->GetBodyList();
      while (_b) {
        Object* obj = static_cast<Object*>(_b->GetUserData());
        if (_b->GetUserData() == nullptr || obj->IsDead()) {
          this->m_World->DestroyBody(_b);
          _b->SetUserData(nullptr);
          if (obj != nullptr) {
            obj->Deleted = true;
          }
        }
        _b = _b->GetNext();
      }

      this->__GetRoom().Move(PlayerPos, m_World);
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
#endif // DEBUG_DRAW
    }

    void Floor::UpdateID(b2Vec2 v)
    {
      unsigned int _x = m_X;
      unsigned int _y = m_Y;
      m_X = (v.x - m_WallWidth) / m_RoomWidth;
      m_Y = (v.y - m_WallHeight) / m_RoomHeight;
      if (m_X != _x || _y != m_Y) {
        m_Rooms.find(_x)->second.find(_y)->second->SweepDeadEntities();
        Notify(this, Util::Event::ROOM_CHANGE);
      }
    }

    std::pair<std::pair<unsigned int, unsigned int>,
      std::pair<unsigned int, unsigned int>>
        Floor::__GenerateRooms(unsigned int cnt)
        {
          unsigned int up = (m_Level * std::rand() % 11 + std::rand() % 37) % cnt;
          unsigned int down = (m_Level * std::rand() % 11 + std::rand() % 37) % cnt;

          std::pair<std::pair<unsigned int, unsigned int>,
            std::pair<unsigned int, unsigned int>>
              res;

          unsigned int _x = 0;
          unsigned int _y = 0;
          unsigned int _cnt = 0;
          unsigned int prev_num = 0;

          while (_cnt < cnt) {
            unsigned int num;
            unsigned int _x_next;
            unsigned int _y_next;

            if (_cnt == up) {
              res.first = std::make_pair(_x, _y);
            }

            if (_cnt == down) {
              res.second = std::make_pair(_x, _y);
            }

            do
              num = (m_Level * std::rand() % 7 + std::rand()) % 4;
            while ((num == 3 && _x == 0) || (num == 0 && _y == 0));

            _x_next = _x + ((num > 1) ? (-1) : 1) * (num % 2);
            _y_next = _y + ((num <= 1) ? (-1) : 1) * !(num % 2);

            // check whether the room already exists
            {
              auto it1 = m_Rooms.find(_x);
              if (it1 != m_Rooms.end()) {
                auto it2 = it1->second.find(_y);
                if (it2 != it1->second.end()) {
                  it2->second->AddDoors((prev_num + 2) % 4);
                  it2->second->AddDoors(num);
                  _x = _x_next;
                  _y = _y_next;
                  prev_num = num;
                  continue;
                }
              }
            }

            // if it does not exist, create it
            RG::Model::Room* tmp_room = new RG::Model::Room(_x, _y);
            b2BodyDef room_bodyDef;
            room_bodyDef.type = b2_dynamicBody;
            room_bodyDef.position.Set(_x * m_RoomWidth, _y * m_RoomHeight);
            tmp_room->m_Body = m_World->CreateBody(&room_bodyDef);

            if (_cnt != 0) {
              tmp_room->AddDoors((prev_num + 2) % 4);
            }

            if (_cnt != cnt - 1) {
              tmp_room->AddDoors(num);
            }
            for (int j = 0; j < std::rand() % 3; ++j) {
              b2BodyDef enemy_bodyDef;
              enemy_bodyDef.type = b2_dynamicBody;
              enemy_bodyDef.position.Set((_x + 0.4 + 0.1 * j) * m_RoomWidth,
                  (_y + 0.4 + 0.1 * j) * m_RoomHeight); // FIXME
              b2Body* enemy_body = m_World->CreateBody(&enemy_bodyDef);

              tmp_room->AddEnemy(enemy_body);
            }
            auto it1 = m_Rooms.find(_x);
            if (it1 == m_Rooms.end()) {
              m_Rooms.insert({ _x, { { _y, tmp_room } } });
            } else {
              it1->second.insert({ _y, tmp_room });
            }

            _x = _x_next;
            _y = _y_next;

            _cnt++;
            prev_num = num;
          }

          // now add walls to all the newly created rooms
          for (auto row : m_Rooms) {
            for (auto cell : row.second) {
              cell.second->AddWalls(m_ScreenWidth, m_ScreenHeight, m_DoorWidth,
                  m_WallWidth, m_WallHeight);
            }
          }

          return res;
        }

    unsigned int Floor::GetRoomId(void) const
    {
      return 1000000 * m_Level + 1000 * m_X + m_Y;
    }

    void Floor::AddStairsObserver(
        RG::Util::Observer* obs, unsigned int x, unsigned int y)
    {
      this->__GetRoom(x, y).AddStairsObserver(obs);
    }

    void Floor::SweepDeadBodies(void) { __GetRoom().SweepDeadEntities(); }
  }
}
