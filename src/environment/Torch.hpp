#pragma once
#include <SFML/Graphics.hpp>

class Torch {
    private:
        sf::Texture texture;
        std::optional<sf::Sprite> sprite;

        sf::Clock animationClock;

        sf::Vector2u position;
    
    public:
        Torch();

        void update();

        void draw(sf::RenderWindow& window);
};