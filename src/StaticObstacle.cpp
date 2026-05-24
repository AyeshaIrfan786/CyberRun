#include "StaticObstacle.h"

StaticObstacle::StaticObstacle(float x) : Obstacle(300.f) {
    position = {x, 360.f};  
}

void StaticObstacle::update(float dt) {
    Obstacle::update(dt);
}

void StaticObstacle::draw(sf::RenderWindow& window) {
    sf::RectangleShape shape({40.f, 60.f});
    shape.setPosition(position);
    shape.setFillColor(sf::Color(255, 50, 50));  
    window.draw(shape);
}