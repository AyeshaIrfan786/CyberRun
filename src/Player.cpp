#include "Player.h"
#include <cmath>

Player::Player() {
    position = {100.f, 400.f};
    velocity = {0.f, 0.f};
}

void Player::jump() {
    if (isGrounded) {
        velocity.y = -700.f;
        isGrounded = false;
    }
}

void Player::update(float dt) {
    velocity.y += gravity * dt;
    position   += velocity * dt;

    if (position.y >= 400.f) {
        position.y = 400.f;
        velocity.y = 0.f;
        isGrounded = true;
    }

    if (isGrounded) legTimer += dt;

    bounds = sf::FloatRect(position, {48.f, 48.f});
}

void Player::draw(sf::RenderWindow& window) {
    // Body
    sf::RectangleShape body({38.f, 44.f});
    body.setPosition(position);
    body.setFillColor(sf::Color(0, 220, 255));
    body.setOutlineThickness(2.f);
    body.setOutlineColor(sf::Color(0, 255, 255));
    window.draw(body);

    // Visor
    sf::RectangleShape visor({22.f, 10.f});
    visor.setPosition({position.x + 8.f, position.y + 8.f});
    visor.setFillColor(sf::Color(255, 50, 50, 220));
    visor.setOutlineThickness(1.f);
    visor.setOutlineColor(sf::Color(255, 100, 100));
    window.draw(visor);

    // Legs
    sf::RectangleShape leg1({10.f, 14.f});
    sf::RectangleShape leg2({10.f, 14.f});

    float legOffset = isGrounded ? std::sin(legTimer * 10.f) * 5.f : 0.f;

    leg1.setPosition({position.x + 2.f, position.y + 44.f});
    leg2.setPosition({position.x + 22.f, position.y + 44.f + legOffset});

    leg1.setFillColor(sf::Color(0, 180, 220));
    leg2.setFillColor(sf::Color(0, 180, 220));

    window.draw(leg1);
    window.draw(leg2);

    if (!isGrounded) {
        sf::RectangleShape jet({14.f, 10.f});
        jet.setPosition({position.x + 12.f, position.y + 44.f});
        jet.setFillColor(sf::Color(255, 140, 0, 200));
        window.draw(jet);
    }
}