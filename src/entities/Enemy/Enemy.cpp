#include "Enemy.hpp"

Enemy::Enemy(float health, float damage, int speed, sf::Vector2f startPosition) {
    this->health = health;
    this->damageDealt = damage;
    this->speed = speed;
    this->position = startPosition;
    this->velocity = sf::Vector2f(0.f, 0.f);
    this->currentState = AnimationState::Idle;
}

float Enemy::getDamageDealt() const {
    return this->damageDealt;
}

void Enemy::takeDamage(float amount) {
    this->health -= amount;

    if(this->health <= 0) {
        this->currentState = AnimationState::Dead;
    }
}

sf::FloatRect Enemy::getHitbox() {
    return sf::FloatRect({position.x - width/2.f, position.y - height/2.f}, {width, height});
}

bool Enemy::isAlive() {
    return health > 0;
}