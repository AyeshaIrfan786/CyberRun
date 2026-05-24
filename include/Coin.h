#pragma once
#include "Entity.h"

class Coin : public Entity {
public:
    bool collected = false;

    Coin(float x, float y);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    bool isOffScreen();
};