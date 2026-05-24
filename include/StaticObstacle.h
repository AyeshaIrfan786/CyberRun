#pragma once
#include "Obstacle.h"

class StaticObstacle : public Obstacle {
public:
    StaticObstacle(float x);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};