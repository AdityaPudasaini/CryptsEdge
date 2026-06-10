#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

class Torch {
    private:
        sf::Texture texture;
        std::optional<sf::Sprite> sprite;

        sf::Clock animationClock;

        sf::Vector2f position;

        int currentFrame;

        Torch(const Torch&) = delete;
        Torch& operator=(const Torch&) = delete;
    
    public:
        Torch(sf::Vector2f position);

        void update();

        void draw(sf::RenderWindow& window);
};