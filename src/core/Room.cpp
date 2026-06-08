#include "Room.hpp"

Room::Room() {
    if(!texture.loadFromFile("./assets/tilesets/dungeon/Tilesetv3.png")) {
        throw std::runtime_error("Fail to load tileset.");
    }

    sprite.emplace(texture);

    for(int i = 0; i < 40; i++) {
        tileMap[0][i] = 1;

        for(int j = 1; j < 11; j++) {
            tileMap[j][i] = 3;
        }

        for(int j = 11; j < 19; j++) {
            tileMap[j][i] = 3;
        }
        tileMap[19][i] = 2;
        tileMap[20][i] = 2;
        tileMap[21][i] = 2;
    }
}

void Room::draw(sf::RenderWindow& window) {
    for(int row = 0; row < 22; row++) {

        for(int col = 0; col < 40; col++) {
            if(tileMap[row][col] == 0) {
                continue;
            }

            if(tileMap[row][col] == 1) {
                sprite->setTextureRect(sf::IntRect({79, 320}, {48, 48}));
                sprite->setPosition({col * 48.f, row * 48.f});
                window.draw(*sprite);
            }

            if(tileMap[row][col] == 2) {
                sprite->setTextureRect(sf::IntRect({79, 320}, {48, 48}));
                sprite->setPosition({col * 48.f, row * 48.f});
                window.draw(*sprite);
            }

            if(tileMap[row][col] == 3) {
                sprite->setTextureRect(sf::IntRect({79, 224}, {48, 48}));
                sprite->setPosition({col * 48.f, row * 48.f});
                window.draw(*sprite);
            }

            if(tileMap[row][col] == 4) {
                sprite->setTextureRect(sf::IntRect({79, 272}, {48, 48}));
                sprite->setPosition({col * 48.f, row * 48.f});
                window.draw(*sprite);
            }
        }
    }
}