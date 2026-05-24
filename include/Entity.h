#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Entity {
public:
    sf::Vector2f position;
    sf::FloatRect bounds;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    virtual ~Entity() {}
};