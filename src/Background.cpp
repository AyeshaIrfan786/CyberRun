#include "Background.h"
#include <cstdlib>

Background::Background() {
    layer1.setSize({800.f, 600.f});
    layer1.setFillColor(sf::Color(5, 5, 20));
    layer1.setPosition({0.f, 0.f});

    ground.setSize({800.f, 152.f});
    ground.setFillColor(sf::Color(20, 20, 35));
    ground.setPosition({0.f, 448.f});

    for (int i = 0; i < 5; i++)
        spawnBuilding();
}

void Background::spawnBuilding() {
    Building b;
    float h = 80.f + rand() % 200;
    float w = 40.f + rand() % 60;
    float x = 800.f + rand() % 400;
    float y = 448.f - h;

    b.shape.setSize({w, h});
    b.shape.setPosition({x, y});

    int colorChoice = rand() % 4;
    sf::Color colors[] = {
        sf::Color(20, 20, 60),
        sf::Color(10, 30, 50),
        sf::Color(25, 15, 45),
        sf::Color(15, 25, 55)
    };
    b.shape.setFillColor(colors[colorChoice]);
    b.shape.setOutlineThickness(1.f);

    int neonChoice = rand() % 3;
    sf::Color neons[] = {
        sf::Color(0, 200, 255, 180),
        sf::Color(180, 0, 255, 180),
        sf::Color(0, 255, 180, 180)
    };
    b.shape.setOutlineColor(neons[neonChoice]);

    b.window1.setSize({8.f, 8.f});
    b.window1.setPosition({x + w*0.25f, y + h*0.2f});
    b.window1.setFillColor(sf::Color(255, 220, 100, 200));

    b.window2.setSize({8.f, 8.f});
    b.window2.setPosition({x + w*0.65f, y + h*0.4f});
    b.window2.setFillColor(sf::Color(100, 200, 255, 200));

    b.speed = 60.f + rand() % 40;
    buildings.push_back(b);
}

void Background::update(float dt) {
    buildingTimer += dt;
    if (buildingTimer > 1.5f) {
        buildingTimer = 0.f;
        spawnBuilding();
    }

    for (auto& b : buildings) {
        b.shape.move({-b.speed * dt, 0.f});
        b.window1.move({-b.speed * dt, 0.f});
        b.window2.move({-b.speed * dt, 0.f});
    }

    for (int i = buildings.size()-1; i >= 0; i--) {
        if (buildings[i].shape.getPosition().x < -200.f)
            buildings.erase(buildings.begin() + i);
    }
}

void Background::draw(sf::RenderWindow& window) {
    window.draw(layer1);
    for (auto& b : buildings) {
        window.draw(b.shape);
        window.draw(b.window1);
        window.draw(b.window2);
    }
    window.draw(ground);
}