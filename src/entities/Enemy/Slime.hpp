#pragma once
#include <SFML/System/Clock.hpp>
#include <optional>
#include <vector>
#include "Enemy.hpp"
#include <string>

class Slime : public Enemy{
    private:
        static std::vector<sf::Texture> frames;
        static bool loaded;

        sf::Clock animationClock, damageClock;
        int currentFrame;
        bool isStunned, hasBeenHit;
        sf::Clock stunClock;

    public:
        Slime(sf::Vector2f position);

        void stun();
        
        bool getIsStunned() const;

        sf::FloatRect getHitbox() override;

        void update(sf::Vector2f playerPosition) override;

        void draw(sf::RenderWindow& window) override;
};