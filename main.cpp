#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "src/entities/Player.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "CryptsEdge", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    Player player;

    while(window.isOpen()) {
        
        while(const auto event = window.pollEvent()) {
            
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            else {
                player.handleInput();
                player.updatePosition();
                player.jump();
            }
        }
    }

    window.clear();
    player.draw(window);
    window.display();

    return 0;
}