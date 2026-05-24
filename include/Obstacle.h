#pragma once
#include "Entity.h"

class Obstacle : public Entity {
public:
    float speed;

    Obstacle(float spd);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    
    bool isOffScreen();
    virtual ~Obstacle() {}
};