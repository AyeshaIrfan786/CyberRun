#include "DynamicObstacle.h"
#include <cmath>

DynamicObstacle::DynamicObstacle(float x) : Obstacle(250.f) {
    position = {x, 250.f};
    startY = 250.f;
}

void DynamicObstacle::update(float dt) {
    sineTimer += dt;
    position.y = startY + std::sin(sineTimer * 3.f) * 60.f;
    Obstacle::update(dt);
}

void DynamicObstacle::draw(sf::RenderWindow& window) {
    sf::RectangleShape shape({40.f, 40.f});
    shape.setPosition(position);
    shape.setFillColor(sf::Color(255, 165, 0));  // orange drone
    window.draw(shape);
}