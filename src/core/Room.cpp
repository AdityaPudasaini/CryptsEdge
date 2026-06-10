#include "Room.hpp"

Room::Room() {
    if(!texture.loadFromFile("./assets/tilesets/dungeon/Tilesetv3.png")) {
        throw std::runtime_error("Fail to load tileset.");
    }

    sprite.emplace(texture);

    for(int col = 0; col < 40; col++) {
        tileMap[19][col] = 3;
        tileMap[20][col] = 3;
        tileMap[21][col] = 3;
    }

    torches.push_back(Torch(sf::Vector2f(300.f, 600.f)));
    torches.push_back(Torch(sf::Vector2f(700.f, 600.f)));
    torches.push_back(Torch(sf::Vector2f(1100.f, 600.f)));
    torches.push_back(Torch(sf::Vector2f(1500.f, 600.f)));
}

void Room::draw(sf::RenderWindow& window) {
    for(int row = 0; row < 22; row++) {

        for(int col = 0; col < 40; col++) {
            if(tileMap[row][col] == 0) {
                continue;
            }

            if(tileMap[row][col] == 3) {
                sprite->setTextureRect(sf::IntRect({80, 321}, {48, 48}));
                sprite->setPosition({col * 48.f, row * 48.f});
                window.draw(*sprite);
            }
        }
    }

    for(auto& torch : torches) {
        torch.draw(window);
    }
}

void Room::update() {
    for(auto& torch : torches) {
        torch.update();
    }
}

float Room::getFloorHeight() {
    return 19 * 48.f;
}