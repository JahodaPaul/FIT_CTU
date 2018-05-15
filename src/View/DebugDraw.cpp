#include "View/DebugDraw.hpp"

namespace RG {
    DebugDraw::DebugDraw( sf::RenderWindow * window ) :
        m_window( window )
    {
        std::cout << "DebugDraw constructor" << std::endl;
    }
    void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        std::cout << "DrawPolygon" << std::endl;
        sf::ConvexShape polygon(vertexCount);
        sf::Vector2f center;
        for(int i = 0; i < vertexCount; i++)
        {
            sf::Vector2f transformedVec = DebugDraw::B2VecToSFVec(vertices[i]);
            polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y)));
        }
        polygon.setOutlineThickness(-1.f);
        polygon.setFillColor(sf::Color::Transparent);
        polygon.setOutlineColor(DebugDraw::GLColorToSFML(color));

        m_window->draw(polygon);
    }
    void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        sf::ConvexShape polygon(vertexCount);
        for(int i = 0; i < vertexCount; i++)
        {
            //polygon.setPoint(i, SFMLDraw::B2VecToSFVec(vertices[i]));
            sf::Vector2f transformedVec = DebugDraw::B2VecToSFVec(vertices[i]);
            polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
        }																								   // they still show up though.. but less frequently
        polygon.setOutlineThickness(-1.f);
        polygon.setFillColor(DebugDraw::GLColorToSFML(color, 60));
        polygon.setOutlineColor(DebugDraw::GLColorToSFML(color));

        m_window->draw(polygon);

    }
    void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
        sf::CircleShape circle(radius * sfdd::SCALE);
        circle.setOrigin(radius * sfdd::SCALE, radius * sfdd::SCALE);
        circle.setPosition(DebugDraw::B2VecToSFVec(center));
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(-1.f);
        circle.setOutlineColor(DebugDraw::GLColorToSFML(color));

        m_window->draw(circle);
    }
    void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
        sf::CircleShape circle(radius * sfdd::SCALE);
        circle.setOrigin(radius * sfdd::SCALE, radius * sfdd::SCALE);
        circle.setPosition(DebugDraw::B2VecToSFVec(center));
        circle.setFillColor(DebugDraw::GLColorToSFML(color, 60));
        circle.setOutlineThickness(1.f);
        circle.setOutlineColor(DebugDraw::GLColorToSFML(color));

        b2Vec2 endPoint = center + radius * axis;
        sf::Vertex line[2] =
        {
            sf::Vertex(DebugDraw::B2VecToSFVec(center), DebugDraw::GLColorToSFML(color)),
            sf::Vertex(DebugDraw::B2VecToSFVec(endPoint), DebugDraw::GLColorToSFML(color)),
        };

        m_window->draw(circle);
        m_window->draw(line, 2, sf::Lines);
    }
    void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
        sf::Vertex line[] =
        {
            sf::Vertex(DebugDraw::B2VecToSFVec(p1), DebugDraw::GLColorToSFML(color)),
            sf::Vertex(DebugDraw::B2VecToSFVec(p2), DebugDraw::GLColorToSFML(color))
        };

        m_window->draw(line, 2, sf::Lines);
    }
    void DebugDraw::DrawTransform(const b2Transform& xf) {
        float lineLength = 0.4;

        /*b2Vec2 xAxis(b2Vec2(xf.p.x + (lineLength * xf.q.c), xf.p.y + (lineLength * xf.q.s)));*/
        b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
        sf::Vertex redLine[] =
        {
            sf::Vertex(DebugDraw::B2VecToSFVec(xf.p), sf::Color::Red),
            sf::Vertex(DebugDraw::B2VecToSFVec(xAxis), sf::Color::Red)
        };

        // You might notice that the ordinate(Y axis) points downward unlike the one in Box2D testbed
        // That's because the ordinate in SFML coordinate system points downward while the OpenGL(testbed) points upward
        /*b2Vec2 yAxis(b2Vec2(xf.p.x + (lineLength * -xf.q.s), xf.p.y + (lineLength * xf.q.c)));*/
        b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
        sf::Vertex greenLine[] =
        {
            sf::Vertex(DebugDraw::B2VecToSFVec(xf.p), sf::Color::Green),
            sf::Vertex(DebugDraw::B2VecToSFVec(yAxis), sf::Color::Green)
        };

        m_window->draw(redLine, 2, sf::Lines);
        m_window->draw(greenLine, 2, sf::Lines);
    }

    sf::Color DebugDraw::GLColorToSFML(const b2Color &color, sf::Uint8 alpha)
    {
        return sf::Color(static_cast<sf::Uint8>(color.r * 255), static_cast<sf::Uint8>(color.g * 255), static_cast<sf::Uint8>(color.b * 255), alpha);
    }

    sf::Vector2f DebugDraw::B2VecToSFVec(const b2Vec2 &vector, bool scaleToPixels)
    {
        return sf::Vector2f(vector.x * (scaleToPixels ? sfdd::SCALE : 1.f), vector.y * (scaleToPixels ? sfdd::SCALE : 1.f));
    }
}
