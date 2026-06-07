#include "Player.hpp"

Player::Player() {
    position = sf::Vector2f(100.f, 900.f);
    velocity = sf::Vector2f(0.f, 0.f);
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

void Player::handleInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        velocity.x = -10.f;
        isFacingRight = false;
        currentState =  AnimationState::Running;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        velocity.x = 10.f;
        isFacingRight = true;
        currentState =  AnimationState::Running;
    }

    else{
        velocity.x = 0.f;
        currentState =  AnimationState::Idle;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isOnGround == true) {
        jump();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
        meleeAttack();
        currentState =  AnimationState::Attacking;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        rangedAttack();
        currentState =  AnimationState::Attacking;
    }
}

Player::~Player() {

}

void Player::jump() {
    velocity.y = - 10.f;
    isOnGround = false;
}

void Player::updatePosition(float timePassed) {
    float gravity = 20.f;    
    velocity.y += gravity * timePassed;

    position.y += velocity.y;
    position.x += velocity.x;
    
    if(position.y >= 900.f) {
        position.y = 900.f;
        velocity.y = 0.f;
        isOnGround = true;
    }
}

sf::FloatRect Player::getHitbox() {
    return sf::FloatRect ({position.x, position.y}, {50.f, 50.f});
}

void Player::damageTaken(float damageAmount) {
    health -= damageAmount;
    currentState = AnimationState::Hurt;

    if(health <= 0) {
        currentState = AnimationState::Dead;
    }
}

void Player::meleeAttack() {
    std::cout << "Melee attack!" << std::endl;
}

void Player::rangedAttack() {
    if(mana >= 10.f) {
        mana -= 10.f;
        std::cout << "Ranged attack! Mana: " << mana << std::endl;
    }
}

void Player::draw(sf::RenderWindow& window) {

    sf::RectangleShape shape({50.f, 50.f});
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
    window.draw(shape);
}