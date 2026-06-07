#pragma once
#include <SFML/Graphics.hpp>
#include <string>
 #include <optional>

class Player
{
    private:
        sf::Vector2f position, velocity;
        float health, mana;
        bool isOnGround, isFacingRight;

        enum class AnimationState {
            Idle,
            Running,
            Attacking,
            Hurt,
            Dead
        };

        AnimationState currentState;

        sf::Texture texture;
        std::optional<sf::Sprite> sprite;

    public:
        Player();

        ~Player();

        sf::Vector2f getPosition() const;
        float getHealth() const;
        float getMana() const;

        void handleInput();

        void updatePosition(float timePassed);

        void jump();

        void meleeAttack();

        void rangedAttack();

        void damageTaken(float damageAmount);

        void draw(sf::RenderWindow& window);

        sf::FloatRect getHitbox();
};
