#pragma once
#include <optional>
#include <vector>
#include "Enemy.hpp"
#include <string>

class Slime : public Enemy{
    private:
        static std::vector<sf::Texture> frames;
        static bool loaded;

        sf::Clock animationClock;
        int currentFrame;

    public:
        Slime(sf::Vector2f position);

        void update(sf::Vector2f playerPosition) override;

        void draw(sf::RenderWindow& window) override;
};