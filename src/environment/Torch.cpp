#include "Torch.hpp"

Torch::Torch(sf::Vector2f position) {
    if(!texture.loadFromFile("./assets/sprites/environment/torch/spr_torch.png ")) {
        throw std::runtime_error("Fail to load the torch texture");
    }

    sprite.emplace(texture);

    currentFrame = 0;
    sprite->setPosition(position);
    sprite->setTextureRect(sf::IntRect({0, 0}, {21, 27}));
}

void Torch::update() {
    if(animationClock.getElapsedTime().asSeconds() >= 0.15f) {
        currentFrame++;

        if(currentFrame >= 4) {
            currentFrame = 0;
        }

        sprite->setTextureRect(sf::IntRect({currentFrame * 21, 0}, {21, 27}));
    }
}

void Torch::draw(sf::RenderWindow& window) {
    window.draw(*sprite);
}