#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../environment/Torch/Torch.hpp"
#include <vector>
#include <memory>

class Room {
    private:
        int tileMap[22][40]{};

        sf::Texture texture;
        std::optional<sf::Sprite> sprite;
        std::vector<std::unique_ptr<Torch>> torches;

    public:
        Room();

        void draw(sf::RenderWindow& window);

        void update();

        float getFloorHeight();
};