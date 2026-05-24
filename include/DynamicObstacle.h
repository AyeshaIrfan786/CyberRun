#pragma once
#include "Obstacle.h"

class DynamicObstacle : public Obstacle {
public:
    float sineTimer = 0.f;
    float startY;

    DynamicObstacle(float x);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};