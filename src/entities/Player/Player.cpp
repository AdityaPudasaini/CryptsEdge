#include "Player.hpp"

Player::Player() {
    position = sf::Vector2f(100.f, 912.f);
    velocity = sf::Vector2f(0.f, 0.f);
    health = 100.f;
    isOnGround = true;
    isFacingRight = true;
    currentState = AnimationState::Idle;
    currentFrameIndex = 0;
    isAttacking = false;
    isInvincible = false;
    damageDealt = 25.f;

    frameDuration[AnimationState::Hurt] = 0.18f;
    frameDuration[AnimationState::Idle] = 0.1f;
    frameDuration[AnimationState::Running] = 0.08f;
    frameDuration[AnimationState::Attacking1] = 0.07f;
    frameDuration[AnimationState::Attacking2] = 0.07f;
    frameDuration[AnimationState::Dead] = 0.15f;
    frameDuration[AnimationState::Jumping] = 0.1f;
    frameDuration[AnimationState::Falling] = 0.1f;

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

float Player::getDamageDealt() const {
    return this->damageDealt;
}

bool Player::getIsAttacking() const {
    return isAttacking;
}

void Player::handleInput() {
    if(!isAttacking) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            isFacingRight = false;

            if(currentState == AnimationState::Hurt) { 
                velocity.x = 0.f; 
                return; 
            }

            velocity.x = -10.f;
            currentState =  AnimationState::Running;
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            isFacingRight = true;

            if(currentState == AnimationState::Hurt) { 
                velocity.x = 0.f; 
                return; 
            }
            
            velocity.x = 10.f;
            currentState =  AnimationState::Running;
        }

        else{
            if(currentState == AnimationState::Hurt) {
                velocity.x = 0.f;
            }

            else if(currentState == AnimationState::Dead) {
                velocity.x = 0.f;
            }

            else {
                velocity.x = 0.f;
                currentState =  AnimationState::Idle;
            }
        }
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
    velocity.y = - 15.f;
    isOnGround = false;
}

void Player::updatePosition(float timePassed) {
    float gravity = 30.f;    
    velocity.y += gravity * timePassed;

    if(velocity.y > 0 && !isOnGround && !isAttacking) {
        currentState = AnimationState::Falling;
    }

    if(isAttacking) {
        velocity.x = 0;
    }

    position.y += velocity.y;
    position.x += velocity.x;
    
    if(position.y >= 912.f) {
        position.y = 912.f;
        velocity.y = 0.f;
        isOnGround = true;
    }
}

void Player::updateAnimation() {
    sprite->setTexture(textures[currentState]);

    if(animationClock.getElapsedTime().asSeconds() >= frameDuration[currentState]) {
        currentFrameIndex++;    
        animationClock.restart();

        if(currentFrameIndex >= totalFrames[currentState]) {
            currentFrameIndex = 0;
            isAttacking = false;    

            if(currentState ==  AnimationState::Hurt) {
                currentState = AnimationState::Idle;
            }
        }

        sprite->setTextureRect(sf::IntRect({currentFrameIndex * 180, 0}, {180, 180}));
    }
}

sf::FloatRect Player::getHitbox() {
    return sf::FloatRect({position.x - 75.f, position.y - 100.f}, {150.f, 200.f});
}

sf::FloatRect Player::getAttackHitbox() {
    if(!isAttacking) return sf::FloatRect({0,0}, {0,0});

    if(isFacingRight) {
        return sf::FloatRect({position.x + 40.f, position.y - 60.f}, {60.f, 60.f});
    } else {
        return sf::FloatRect({position.x - 100.f, position.y - 60.f}, {60.f, 60.f});
    }
}

void Player::damageTaken(float damageAmount) {
    if(!isInvincible) {
        health -= damageAmount;
        currentState = AnimationState::Hurt;
        std::cout << "Current State: " << (int)currentState << std::endl;

        if(health <= 0) {
            currentState = AnimationState::Dead;
        }

        isInvincible = true;
        damageClock.restart();
    }

    if(damageClock.getElapsedTime().asSeconds() >= 1.f) {
        isInvincible = false;
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
        std::cout << "Melee attack 2!" << std::endl;
        meleeClock.restart();
    }
}

void Player::draw(sf::RenderWindow& window) {
    sprite->setOrigin({180.f / 2.f, 180.f / 2.f});

    if(isFacingRight) {
        sprite->setScale({2.f, 2.f});
        sprite->setPosition(position);
    } 
    
    else {
        sprite->setScale({-2.f, 2.f});
        sprite->setPosition({position.x + 180.f, position.y});
    }

    sprite->setPosition(position);
    window.draw(*sprite);
}