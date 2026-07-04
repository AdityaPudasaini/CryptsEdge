#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "src/entities/Player/Player.hpp"
#include "src/core/Room/Room.hpp"
#include "src/entities/Enemy/Slime.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "CryptsEdge", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    Room room;
    Player player;
    Slime slime(sf::Vector2f(800.f, 912.f));
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
        slime.update(player.getPosition());

        if(player.getHitbox().findIntersection(slime.getHitbox())){
            player.damageTaken(slime.getDamageDealt());
        }

        player.updateAnimation();

        window.clear(sf::Color(15, 10, 25));
        room.draw(window);
        room.update();
        player.draw(window);
        slime.draw(window);
        window.display();

        if(player.getHealth() <= 0.0) {
            window.close();
        }
    }
    
    return 0;
}