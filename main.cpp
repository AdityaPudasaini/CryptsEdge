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

        if(slime.isAlive()) {
            slime.update(player.getPosition());

            if(player.getHitbox().findIntersection(slime.getHitbox())) {
                player.damageTaken(slime.getDamageDealt());
            }

            if(player.getIsAttacking() && player.getAttackHitbox().findIntersection(slime.getHitbox())) {
                if(!slime.getIsStunned()) {
                    slime.takeDamage(player.getDamageDealt());
                    slime.stun();
                }
            }
        }

        player.updateAnimation();

        window.clear(sf::Color(15, 10, 25));
        room.draw(window);
        room.update();
        player.draw(window);

        if(slime.isAlive()) {
            slime.draw(window);
        }

        if(player.getHealth() <= 0.f) {
            window.close();
        }

        /*
        sf::RectangleShape attackRect(player.getAttackHitbox().size);
        attackRect.setPosition(player.getAttackHitbox().position);
        attackRect.setFillColor(sf::Color(255, 0, 0, 100));
        window.draw(attackRect);

        sf::RectangleShape slimeRect(slime.getHitbox().size);
        slimeRect.setPosition(slime.getHitbox().position);
        slimeRect.setFillColor(sf::Color(0, 255, 0, 100));
        window.draw(slimeRect);
        */

        window.display();
    }
    
    return 0;
}