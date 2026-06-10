#pragma once
#include <optional>
#include <vector>
#include "Enemy.hpp"

class Slime : public Enemy{
    private:
        std::vector<sf::Texture> frames;

        sf::Clock animationClock;
        int currentFrame;

    public:
        Slime(sf::Vector2f position);

        void update(sf::Vector2f playerPosition) override;

        void draw(sf::RenderWindow& window) override;
};