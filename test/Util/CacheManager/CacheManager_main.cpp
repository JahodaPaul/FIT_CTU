#include "Util/CacheManager.hpp"

using namespace RG;

int main(void){

    CacheManager cacheManager;

    std::pair<std::string, std::shared_ptr<sf::Texture>> txtr;
    std::pair<std::string, std::shared_ptr<sf::Texture>> txtr2;
    std::pair<std::string, std::shared_ptr<sf::Texture>> txtr3;
    std::pair<std::string, std::shared_ptr<sf::Texture>> txtr4;
    std::pair<std::string, std::shared_ptr<sf::Texture>> txtr5;

    txtr = cacheManager.getTexture("bg.png");
    txtr2 = cacheManager.getTexture("bg.png");
    txtr3 = cacheManager.getTexture("bg.png");
    txtr4 = cacheManager.getTexture("bg.png");

    cacheManager.deleteTexture("bg.png");
    cacheManager.deleteTexture("bg.png");
    cacheManager.deleteTexture("bg.png");
    cacheManager.deleteTexture("bg.png");

    txtr5 = cacheManager.getTexture("bg.png");

    sf::RenderWindow window(sf::VideoMode(800,600), "Test Window", sf::Style::Default, sf::ContextSettings{ 0u, 0u, 4u, 1u, 1u, 0u, false });

    sf::Event event;
    while(window.isOpen()){
        sf::Sprite sprite(*txtr5.second);
        window.draw(sprite);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.display();
        window.clear();
    }

    return 0;
}