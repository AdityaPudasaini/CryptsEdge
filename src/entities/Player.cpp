#include "Player.hpp"

Player::Player() {
    position = sf::Vector2f(100.f, 900.f);
    velocity = sf::Vector2f(0.f, 0.f);
    health = 100.f;
    isOnGround = true;
    isFacingRight = true;
    currentState = AnimationState::Idle;
    currentFrameIndex = 0;
    isAttacking = false;

    if(!textures[AnimationState::Idle].loadFromFile("./assets/sprites/player/hero_knight/Idle.png")) {
        throw std::runtime_error("Failed to load texture for idle");
    }

    if(!textures[AnimationState::Running].loadFromFile("./assets/sprites/player/hero_knight/Run.png")) {
        throw std::runtime_error("Failed to load texture for run");
    }

    if(!textures[AnimationState::Attacking1].loadFromFile("./assets/sprites/player/hero_knight/Attack1.png")) {
        throw std::runtime_error("Failed to load texture for attack1");
    }

    if(!textures[AnimationState::Attacking2].loadFromFile("./assets/sprites/player/hero_knight/Attack2.png")) {
        throw std::runtime_error("Failed to load texture for attack2");
    }

    if(!textures[AnimationState::Jumping].loadFromFile("./assets/sprites/player/hero_knight/Jump.png")) {
        throw std::runtime_error("Failed to load texture for jump");
    }

    if(!textures[AnimationState::Falling].loadFromFile("./assets/sprites/player/hero_knight/Fall.png")) {
        throw std::runtime_error("Failed to load texture for fall");
    }

    if(!textures[AnimationState::Hurt].loadFromFile("./assets/sprites/player/hero_knight/Hurt.png")) {
        throw std::runtime_error("Failed to load texture for hurt");
    }

    if(!textures[AnimationState::Dead].loadFromFile("./assets/sprites/player/hero_knight/Death.png")) {
        throw std::runtime_error("Failed to load texture for death");
    }

    totalFrames[AnimationState::Idle] = 11;
    totalFrames[AnimationState::Running] = 8;
    totalFrames[AnimationState::Attacking1] = 7;
    totalFrames[AnimationState::Attacking2] = 7;
    totalFrames[AnimationState::Jumping] = 3;
    totalFrames[AnimationState::Falling] = 3;
    totalFrames[AnimationState::Hurt] = 4;
    totalFrames[AnimationState::Dead] = 11;

    sprite.emplace(textures[AnimationState::Idle]);
    sprite->setScale({2.f, 2.f});
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
        currentState =  AnimationState::Jumping;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
        if(!isAttacking) {
            currentFrameIndex = 0;
            meleeAttack1();
            currentState =  AnimationState::Attacking1;
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        if(!isAttacking) {
            currentFrameIndex = 0;
            meleeAttack2();
            currentState =  AnimationState::Attacking2;
        }
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

void Player::updateAnimation() {
    sprite->setTexture(textures[currentState]);

    if(animationClock.getElapsedTime().asSeconds() >= 0.1f) {
        currentFrameIndex++;
        animationClock.restart();

        if(currentFrameIndex >= totalFrames[currentState]) {
            currentFrameIndex = 0;
            isAttacking = false;    
        }

        sprite->setTextureRect(sf::IntRect({currentFrameIndex * 180, 0}, {180, 180}));
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
    isAttacking = true;
    if(meleeClock.getElapsedTime().asSeconds() >= 0.5f) {
        std::cout << "Melee attack 1!" << std::endl;
        meleeClock.restart();
    }
}

void Player::meleeAttack2() {
    isAttacking = true;
    if(meleeClock.getElapsedTime().asSeconds() >= 0.5f) {
        std::cout << "Melee attack 1!" << std::endl;
        meleeClock.restart();
    }
}

void Player::draw(sf::RenderWindow& window) {
    sprite->setPosition(position);
    window.draw(*sprite);
}