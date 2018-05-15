#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace RG {
    namespace sfdd
    {
        const float SCALE = 32.f;
    }

    class DebugDraw : public b2Draw
    {
        public:
            DebugDraw(sf::RenderWindow * window );
            void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
            void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
            void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
            void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
            void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
            void DrawTransform(const b2Transform& xf);
        private:
            static sf::Color GLColorToSFML(const b2Color &color, sf::Uint8 alpha = 255);
            static sf::Vector2f B2VecToSFVec(const b2Vec2 &vector, bool scaleToPixels = true);

            sf::RenderWindow * m_window;
    };

}
