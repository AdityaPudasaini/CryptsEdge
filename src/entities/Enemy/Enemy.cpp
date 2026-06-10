#include "Enemy.hpp"

Enemy::Enemy(float health, float damage, int speed, sf::Vector2f startPosition) {
    this->health = health;
    this->damageDealt = damage;
    this->speed = speed;
    this->position = startPosition;
    this->velocity = sf::Vector2f(0.f, 0.f);
    this->currentState = AnimationState::Idle;
}

void Enemy::takeDamage(float amount) {
    this->health -= amount;

    if(this->health <= 0) {
        this->currentState = AnimationState::Dead;
    }
}

sf::FloatRect Enemy::getHitbox() {
    return sf::FloatRect({this->position.x, this->position.y}, {50, 50});
}

bool Enemy::isAlive() {
    return health > 0;
}