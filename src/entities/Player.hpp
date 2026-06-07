#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct Player
{
    sf::Vector2f position;
    int velocity;
    float health, mana;
    bool isOnGround, isFacingRight;

    enum class currentAnimationState {
        Idle,
        Running,
        Attacking,
        Hurt,
        Dead
    };

    sf::Texture texture;
    sf::Sprite sprite;

    
};
