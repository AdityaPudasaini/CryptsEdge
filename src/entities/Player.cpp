#include "Player.hpp"

Player::Player() {
    position = sf::Vector2f(100.f, 900.f);
    velocity = sf::Vector2f(0.f, 0.f);
    health = 100.f;
    isOnGround = true;
    isFacingRight = true;
    currentState = AnimationState::Idle;
    currentFrameIndex = 0;

    textures[AnimationState::Idle].loadFromFile("./assets/sprites/player/hero_knight/Idle.png");
    textures[AnimationState::Running].loadFromFile("./assets/sprites/player/hero_knight/Run.png");
    textures[AnimationState::Attacking1].loadFromFile("./assets/sprites/player/hero_knight/Attack1.png");
    textures[AnimationState::Attacking2].loadFromFile("./assets/sprites/player/hero_knight/Attack2.png");
    textures[AnimationState::Jumping].loadFromFile("./assets/sprites/player/hero_knight/Jump.png");
    textures[AnimationState::Falling].loadFromFile("./assets/sprites/player/hero_knight/Fall.png");
    textures[AnimationState::Hurt].loadFromFile("./assets/sprites/player/hero_knight/Hurt.png");
    textures[AnimationState::Dead].loadFromFile("./assets/sprites/player/hero_knight/Death.png");

    sprite.emplace(textures[AnimationState::Idle]);
}

sf::Vector2f Player::getPosition() const{
    return this->position;
}
float Player::getHealth() const {
    return this->health;
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
        meleeAttack1();
        currentState =  AnimationState::Attacking1;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        meleeAttack2();
        currentState =  AnimationState::Attacking2;
    }
}

Player::~Player() {

}

void Player::jump() {
    velocity.y = - 10.f;
    isOnGround = false;
    currentState =  AnimationState::Jumping;
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

void Player::meleeAttack1() {
    if(meleeClock.getElapsedTime().asSeconds() >= 0.5f) {
        std::cout << "Melee attack 1!" << std::endl;
        meleeClock.restart();
    }
}

void Player::meleeAttack2() {
    if(meleeClock.getElapsedTime().asSeconds() >= 0.5f) {
        std::cout << "Melee attack 1!" << std::endl;
        meleeClock.restart();
    }
}

void Player::draw(sf::RenderWindow& window) {

    sf::RectangleShape shape({50.f, 50.f});
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
    window.draw(shape);
}