#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Background {
public:
    sf::RectangleShape layer1;
    sf::RectangleShape ground;

    struct Building {
        sf::RectangleShape shape;
        sf::RectangleShape window1, window2;
        float speed;
    };

    std::vector<Building> buildings;
    float buildingTimer = 0.f;

    Background();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void spawnBuilding();
};