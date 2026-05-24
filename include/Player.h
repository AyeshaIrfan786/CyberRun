#pragma once
#include "Entity.h"

class Player : public Entity {
public:
    sf::Vector2f velocity;
    float gravity   = 1500.f;
    bool  isGrounded = false;
    float legTimer   = 0.f;

    Player();
    void jump();
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};