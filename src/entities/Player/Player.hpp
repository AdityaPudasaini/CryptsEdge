#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include <iostream>
#include <map>

class Player
{
    private:
        sf::Vector2f position, velocity;
        float health;
        bool isOnGround, isFacingRight, isAttacking;
        sf::Clock meleeClock, rangedClock, animationClock, damageClock ;
        int currentFrameIndex;

        enum class AnimationState {
            Idle,
            Running,
            Attacking1,
            Attacking2,
            Jumping,
            Falling,
            Hurt,
            Dead
        };

        AnimationState currentState;

        std::map<AnimationState, sf::Texture> textures;
        std::map<AnimationState, int> totalFrames;
        std::optional<sf::Sprite> sprite;

    public:
        Player();

        ~Player();

        sf::Vector2f getPosition() const;
        float getHealth() const;

        void handleInput();

        void updatePosition(float timePassed);

        void updateAnimation();

        void jump();

        void meleeAttack1();

        void meleeAttack2();

        void damageTaken(float damageAmount);

        void draw(sf::RenderWindow& window);

        sf::FloatRect getHitbox();
};
