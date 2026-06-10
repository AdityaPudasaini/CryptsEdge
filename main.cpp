#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "src/entities/Player/Player.hpp"
#include "src/core/Room/Room.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "CryptsEdge", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    Room room;
    Player player;
    sf::Clock time;

    while(window.isOpen()) {

        float timePassed = time.restart().asSeconds();
        
        while(const auto event = window.pollEvent()) {
            
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        player.handleInput();
        player.updatePosition(timePassed);
        player.updateAnimation();

        window.clear(sf::Color(15, 10, 25));
        room.draw(window);
        room.update();
        player.draw(window);
        window.display();
    }
    
    return 0;
}