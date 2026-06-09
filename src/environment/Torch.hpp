#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Torch {
    private:
        sf::Texture texture;
        std::optional<sf::Sprite> sprite;

        sf::Clock animationClock;

        sf::Vector2f position;

        int currentFrame;
    
    public:
        Torch(sf::Vector2f position);

        void update();

        void draw(sf::RenderWindow& window);
};