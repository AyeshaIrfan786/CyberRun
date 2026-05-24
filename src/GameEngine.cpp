#include "GameEngine.h"
#include <cstdlib>
#include <ctime>

GameEngine::GameEngine() 
    : window(sf::VideoMode({800, 600}), "Endless Cyber Runner") {
    
    window.setFramerateLimit(60);
    srand(time(0));

    if (!font.openFromFile("assets/font.ttf")) {
     
    }

    scoreText    = new sf::Text(font, "Score: 0", 28);
    gameOverText = new sf::Text(font, "GAME OVER!", 64);
    restartText  = new sf::Text(font, "Press R to Restart", 32);

    scoreText->setFillColor(sf::Color::White);
    scoreText->setPosition({20.f, 20.f});

    gameOverText->setFillColor(sf::Color(255, 50, 50));
    gameOverText->setPosition({150.f, 200.f});

    restartText->setFillColor(sf::Color::White);
    restartText->setPosition({230.f, 300.f});

    ground.setSize({800.f, 20.f});
    ground.setFillColor(sf::Color(50, 50, 50));
    ground.setPosition({0.f, 448.f});
}

void GameEngine::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        handleEvents();
        update(dt);
        draw();
    }
}

void GameEngine::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (event->is<sf::Event::KeyPressed>()) {
            auto* key = event->getIf<sf::Event::KeyPressed>();
            
            if (key->code == sf::Keyboard::Key::Space 
                && state == GameState::PLAYING)
                player.jump();

            if (key->code == sf::Keyboard::Key::R 
                && state == GameState::GAME_OVER)
                resetGame();
        }
    }
}

void GameEngine::update(float dt) {
    if (state == GameState::GAME_OVER) return;

    background.update(dt);  // Fixed: moved here, removed duplicate nested function

    scoreTimer += dt;
    if (scoreTimer >= 0.5f) {
        score++;
        scoreTimer = 0.f;
        scoreText->setString("Score: " + std::to_string(score));
    }

    gameSpeed = 1.f + (score * 0.05f);

    spawnTimer += dt;
    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0.f;
        spawnInterval = 1.5f + (rand() % 10) / 10.f;
        spawnObstacle();
        if (score % 3 == 0)
            spawnCoin();
    }

    player.update(dt);

    for (Entity* e : obstacles)
        e->update(dt);

    for (Coin* c : coins)
        c->update(dt);

    checkCollisions();

    for (int i = obstacles.size() - 1; i >= 0; i--) {
        Obstacle* obs = dynamic_cast<Obstacle*>(obstacles[i]);
        if (obs && obs->isOffScreen()) {
            delete obstacles[i];
            obstacles.erase(obstacles.begin() + i);
        }
    }

    for (int i = coins.size() - 1; i >= 0; i--) {
        if (coins[i]->isOffScreen() || coins[i]->collected) {
            delete coins[i];
            coins.erase(coins.begin() + i);
        }
    }
}

void GameEngine::spawnObstacle() {
    int type = rand() % 2;
    if (type == 0)
        obstacles.push_back(new StaticObstacle(850.f));
    else
        obstacles.push_back(new DynamicObstacle(850.f));
}

void GameEngine::spawnCoin() {
    float y = 300.f + (rand() % 100);
    coins.push_back(new Coin(850.f, y));
}

void GameEngine::checkCollisions() {
    for (Entity* e : obstacles) {
        if (player.bounds.findIntersection(e->bounds)) {
            state = GameState::GAME_OVER;
            return;
        }
    }

    for (Coin* c : coins) {
        if (!c->collected && 
            player.bounds.findIntersection(c->bounds)) {
            c->collected = true;
            score += 5;
            scoreText->setString("Score: " + std::to_string(score));
        }
    }
}

void GameEngine::resetGame() {
    cleanup();
    score = 0;
    scoreTimer = 0.f;
    spawnTimer = 0.f;
    spawnInterval = 2.f;
    gameSpeed = 1.f;
    state = GameState::PLAYING;
    player = Player();
    scoreText->setString("Score: 0");
}

void GameEngine::draw() {
    window.clear(sf::Color(5, 5, 20));
    background.draw(window);
    window.draw(ground);
    player.draw(window);

    for (Entity* e : obstacles)
        e->draw(window);

    for (Coin* c : coins)
        c->draw(window);

    window.draw(*scoreText);

    if (state == GameState::GAME_OVER) {
        window.draw(*gameOverText);
        window.draw(*restartText);
    }

    window.display();
}

void GameEngine::cleanup() {
    for (Entity* e : obstacles) delete e;
    obstacles.clear();
    for (Coin* c : coins) delete c;
    coins.clear();
}