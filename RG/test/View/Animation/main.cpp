#include "View/Animation.hpp"

//DISCLAIMER
//This is just test of Animation class, user input is handled realy
//badly and this code should not be used as any sort of inspiration!
int main(int argc, char ** argv){
    using namespace RG;
    sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Demo Game");
    renderWindow.setVerticalSyncEnabled(true);
    sf::Clock clock;

    sf::Event event;
    Animation player( "playerFrames.png", 91, 91, 12, 50 );
    player.setPosition({50, 50});
    player.setRotation( 180 );

    while (renderWindow.isOpen()){
        while (renderWindow.pollEvent(event)){
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();
            if (event.type == sf::Event::KeyPressed) {
                player.startAnimation();
                if (event.key.code == sf::Keyboard::Left) {
                    player.setPosition( player.getPosition() + sf::Vector2f{-10,0} );
                    player.setRotation( 270 );
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    player.setPosition( player.getPosition() + sf::Vector2f{10,0} );
                    player.setRotation( 90 );
                }
                else if (event.key.code == sf::Keyboard::Up)  {
                    player.setPosition( player.getPosition() + sf::Vector2f{0,-10} );
                    player.setRotation( 0 );
                }
                else if (event.key.code == sf::Keyboard::Down)  {
                    player.setPosition( player.getPosition() + sf::Vector2f{0,10} );
                    player.setRotation( 180 );
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                player.stopAnimation();
                player.goToFrame( 0 );
            }
        }

        renderWindow.clear();
        player.update( clock.getElapsedTime().asMilliseconds() );
        renderWindow.draw(player);
        renderWindow.display();
    }
}
