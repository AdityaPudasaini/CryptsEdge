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

void Player::jump() {
    velocity.y = - 20.f;
    isOnGround = false;
}

void Player::updatePosition(float timePassed) {
    float gravity = 15.f;    
    velocity.y += gravity * timePassed;

    position.y += velocity.y;
    position.x = velocity.x;
    
    if(position.y >= 900.f) {
        position.y = 900.f;
        velocity.y = 0.f;
        isOnGround = true;
    }
}

void Player::draw(sf::RenderWindow& window) {

    sf::RectangleShape shape({50.f, 50.f});
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
    window.draw(shape);
}