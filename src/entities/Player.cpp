#include "Player.hpp"

Player::Player() {
    position = sf::Vector2f(100.f, 900.f);
    health = 100.f;
    mana = 50.f;
    isOnGround = true;
    isFacingRight = true;
    currentState = AnimationState::Idle;
}


