#include "Player.hpp"

Player::Player() {
    position = sf::Vector2f(100.f, 900.f);
    health = 100.f;
    mana = 50.f;
    isOnGround = true;
    isFacingRight = true;
    currentState = AnimationState::Idle;
}

sf::Vector2f Player::getPosition() const{
    return this->position;
}
float Player::getHealth() const {
    return this->health;
}
float Player::getMana() const {
    return this->mana;
}

