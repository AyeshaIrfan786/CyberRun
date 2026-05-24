#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.h"
#include "StaticObstacle.h"
#include "DynamicObstacle.h"
#include "Coin.h"
#include "Background.h"        

enum class GameState {
    PLAYING,
    GAME_OVER
};

class GameEngine {
public:
    sf::RenderWindow window;
    Player player;
    Background background;     

    std::vector<Entity*> obstacles;
    std::vector<Coin*> coins;

    GameState state = GameState::PLAYING;

    int score = 0;
    float scoreTimer = 0.f;
    float spawnTimer = 0.f;
    float spawnInterval = 2.f;
    float gameSpeed = 1.f;

    sf::Font font;
    sf::Text* scoreText    = nullptr;
    sf::Text* gameOverText = nullptr;
    sf::Text* restartText  = nullptr;

    sf::RectangleShape ground;

    GameEngine();
    void run();
    void handleEvents();
    void update(float dt);
    void draw();
    void spawnObstacle();
    void spawnCoin();
    void checkCollisions();
    void resetGame();
    void cleanup();
};