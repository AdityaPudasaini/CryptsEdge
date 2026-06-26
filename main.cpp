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
        player.updateAnimation();
        slime.update(player.getPosition());

        auto playerHB = player.getHitbox();
auto slimeHB = slime.getHitbox();
std::cout << "Player: " << playerHB.position.x << "," << playerHB.position.y 
          << " size: " << playerHB.size.x << "," << playerHB.size.y << std::endl;
std::cout << "Slime: " << slimeHB.position.x << "," << slimeHB.position.y 
          << " size: " << slimeHB.size.x << "," << slimeHB.size.y << std::endl;
        if(player.getHitbox().findIntersection(slime.getHitbox())){
            player.damageTaken(slime.getDamageDealt());
        }

        window.clear(sf::Color(15, 10, 25));
        room.draw(window);
        room.update();
        player.draw(window);
        slime.draw(window);
        window.display();
    }
    
    return 0;
}