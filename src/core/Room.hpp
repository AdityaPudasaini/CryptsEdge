#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Room {
    private:
        int tileMap[22][40]{};

        sf::Texture texture;
        std::optional<sf::Sprite> sprite;

    public:
        Room();

        void draw(sf::RenderWindow& window);

        float getFloorHeight();
};