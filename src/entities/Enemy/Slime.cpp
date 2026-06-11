#include "Slime.hpp"

std::vector<sf::Texture> Slime::frames;
bool Slime::loaded = false;

Slime::Slime(sf::Vector2f position) : Enemy(50.f, 10.f, 2, position){
    if(!loaded) {
        
        for(int i = 0; i < 30; i++) {

            if(i < 10) {
                frames.emplace_back();
                if(!frames.back().loadFromFile("./assets/sprites/enemies/Slimes/SlimeGreen/SlimeBasic_000" + std::to_string(i))) {
                    throw std::runtime_error("Fail to load texture");
                }
            }

            else {
                frames.emplace_back();
                if(!frames.back().loadFromFile("./assets/sprites/enemies/Slimes/SlimeGreen/SlimeBasic_0000" + std::to_string(i))) {
                    throw std::runtime_error("Fail to load texture");
                }
            }
        }

        loaded = true;
    }

    currentFrame = 0;
    sprite.emplace(frames[0]);
    sprite->setScale({2.f, 2.f});
    sprite->setPosition(position);

}

void Slime::update(sf::Vector2f playerPosition) {
    
}

void Slime::draw(sf::RenderWindow& window) {
    
}