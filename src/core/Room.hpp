#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../environment/Torch.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>

class Room {
    private:
        int tileMap[22][40]{};

        sf::Texture texture;
        std::optional<sf::Sprite> sprite;
        std::vector<Torch> torches;

    public:
        Room();

        void draw(sf::RenderWindow& window);

        void update();

        float getFloorHeight();
};