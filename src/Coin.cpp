#include "Coin.h"

Coin::Coin(float x, float y) {
    position = {x, y};
}

void Coin::update(float dt) {
    position.x -= 300.f * dt;
    bounds = sf::FloatRect(position, {20.f, 20.f});
}

void Coin::draw(sf::RenderWindow& window) {
    if (!collected) {
        sf::CircleShape shape(10.f);
        shape.setPosition(position);
        shape.setFillColor(sf::Color(255, 215, 0));
        window.draw(shape);
    }
}

bool Coin::isOffScreen() {
    return position.x < -30.f;
}