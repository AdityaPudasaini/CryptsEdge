#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Enemy {
    protected:
        sf::Vector2f position, velocity;
        float health, damageDealt;
        int speed;

        sf::Texture texture;
        std::optional<sf::Sprite> sprite;

        enum class AnimationState {
            Idle,
            Dead
        };

        AnimationState currentState;

        sf::FloatRect hitbox;

    public:
        Enemy();

        virtual ~Enemy() = default;

        virtual void update(sf::Vector2f playerPosition) = 0;

        virtual void draw(sf::RenderWindow& window) = 0;

        void takeDamage(float amount);

        sf::FloatRect getHitbox();

        bool isAlive();
};