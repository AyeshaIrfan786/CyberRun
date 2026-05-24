#include "Obstacle.h"

Obstacle::Obstacle(float spd) {
    speed = spd;
}

void Obstacle::update(float dt) {
    position.x -= speed * dt;
    bounds = sf::FloatRect(position, {40.f, 40.f});
}

void Obstacle::draw(sf::RenderWindow& window) {
    sf::RectangleShape shape({40.f, 40.f});
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);
}

bool Obstacle::isOffScreen() {
    return position.x < -50.f;
}