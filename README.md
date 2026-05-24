#Cyber Runner


---

## What is this game?

Endless Cyber Runner is a fast-paced 2D side-scrolling arcade game built in **C++** using the **SFML** (Simple and Fast Multimedia Library) framework. The player controls a cyber-themed character that runs automatically through a procedurally generated obstacle course. The goal is to survive as long as possible by jumping over obstacles and collecting coins to boost your score.

The entire project is designed and implemented around core **Object-Oriented Programming** principles — every game entity and system is represented as a class.

---

## How to play

| Key | Action |
|-----|--------|
| `SPACE` | Jump over obstacles |
| `R` | Restart after Game Over |

**Objective:** Survive as long as possible. Collect coins for bonus points (+5 each). The world speeds up as your score increases. Try to beat your previous run.

---

## Features

- **Endless runner gameplay** — the world scrolls faster as your score climbs
- **Two obstacle types** — static spike barriers and dynamic bouncing obstacles
- **Coin collection** — coins spawn periodically for bonus score
- **Scrolling parallax background** — cyber-themed environment that tiles seamlessly
- **Real-time score display** — updates every 0.5 seconds on screen
- **Game Over screen** — with prompt to restart
- **Increasing difficulty** — `gameSpeed` scales with score automatically

---

## Project structure

```
Endless Cyber Runner/
├── assets/
│   └── font.ttf
├── include/
│   ├── Entity.h
│   ├── Player.h
│   ├── Obstacle.h
│   ├── StaticObstacle.h
│   ├── DynamicObstacle.h
│   ├── Coin.h
│   ├── Background.h
│   └── GameEngine.h
└── src/
    ├── main.cpp
    ├── GameEngine.cpp
    ├── Player.cpp
    ├── Obstacle.cpp
    ├── StaticObstacle.cpp
    ├── DynamicObstacle.cpp
    ├── Coin.cpp
    └── Background.cpp
```

---

## OOP concepts demonstrated

### 1. Encapsulation
Every game entity bundles its own data and behaviour inside a class. `Player` manages its own position, velocity, and gravity internally. `GameEngine` manages the game loop, score, spawn timers, and window — none of these details leak into other classes. Each class exposes only what other classes need through its public interface.

### 2. Inheritance
```
Entity  (abstract base class)
├── Player
├── Coin
└── Obstacle  (intermediate base class)
    ├── StaticObstacle
    └── DynamicObstacle
```

`Entity` defines the shared interface (`update()`, `draw()`, `bounds`, `isOffScreen()`). `Obstacle` adds scrolling speed behaviour shared by both obstacle types. `StaticObstacle` and `DynamicObstacle` each override `draw()` to render differently without duplicating the movement logic.

### 3. Polymorphism
`GameEngine` stores all obstacles in a single `std::vector<Entity*>`. Calling `update()` and `draw()` on each pointer automatically dispatches to the correct subclass method at runtime through virtual functions — no `if/else` type checking needed anywhere.

```cpp
// One loop handles all obstacle types through base pointer
for (Entity* e : obstacles)
    e->update(dt);

for (Entity* e : obstacles)
    e->draw(window);
```

The `DynamicObstacle` overrides `update()` to add a sine-wave vertical bounce on top of horizontal movement, while `StaticObstacle` inherits the base movement unchanged.

### 4. Dynamic memory management
Obstacles and coins are created at runtime using `new` when spawned and destroyed using `delete` when they scroll off screen or are collected. The `cleanup()` function clears all vectors safely on game reset. The base class destructor is declared `virtual` to ensure correct cleanup through base pointers.

```cpp
void GameEngine::spawnObstacle() {
    int type = rand() % 2;
    if (type == 0)
        obstacles.push_back(new StaticObstacle(850.f));
    else
        obstacles.push_back(new DynamicObstacle(850.f));
}

void GameEngine::cleanup() {
    for (Entity* e : obstacles) delete e;
    obstacles.clear();
    for (Coin* c : coins) delete c;
    coins.clear();
}
```

---

## How to build

Make sure SFML is installed via MSYS2/UCRT64 on Windows.

```bash
g++.exe src/main.cpp src/GameEngine.cpp src/Background.cpp \
        src/Player.cpp src/Obstacle.cpp src/StaticObstacle.cpp \
        src/DynamicObstacle.cpp src/Coin.cpp \
        -Iinclude \
        -IC:/msys64/ucrt64/include \
        -LC:/msys64/ucrt64/lib \
        -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
        -o CyberRunner.exe
```

Run:
```bash
./CyberRunner.exe
```

> Make sure `assets/font.ttf` is present. The game window will open at 800×600.

---

## Class diagram

```
┌──────────────────────────────────────────────────┐
│                   GameEngine                     │
│──────────────────────────────────────────────────│
│ window, font, state, score                       │
│ player, background                               │
│ obstacles : vector<Entity*>                      │
│ coins     : vector<Coin*>                        │
│──────────────────────────────────────────────────│
│ run(), handleEvents(), update(), draw()          │
│ spawnObstacle(), spawnCoin()                     │
│ checkCollisions(), resetGame(), cleanup()        │
└──────────────────────────────────────────────────┘
                        │
          ┌─────────────┼──────────────┐
          │             │              │
       Player         Coin         Entity* (base)
                                       │
                                   Obstacle
                                  ┌────┴────┐
                            StaticObstacle  DynamicObstacle
```

---

## Game systems explained

### Game loop
`GameEngine::run()` uses an `sf::Clock` to compute delta time each frame and passes it to `update()` and `draw()`. The window runs at a capped 60 FPS.

### Spawning system
`spawnTimer` accumulates delta time each frame. When it exceeds `spawnInterval`, a new obstacle spawns at x=850 (just off the right edge) and `spawnInterval` is randomised again between 1.5 and 2.5 seconds. Coins spawn every 3rd score point.

### Difficulty scaling
```cpp
gameSpeed = 1.f + (score * 0.05f);
```
Every entity's movement is multiplied by `gameSpeed`, so the whole world accelerates together as the score grows.

### Collision detection
`sf::FloatRect::findIntersection()` checks bounding box overlaps between the player and each obstacle or coin each frame. A hit with an obstacle triggers Game Over; a hit with a coin marks it as collected and awards +5 points.

### Background scrolling
`Background` tiles its visual elements by tracking an `offset` that increases each frame. When the offset exceeds the tile width (800px) it wraps back to zero, creating seamless infinite scroll.

---

## Technologies used

| Tool | Purpose |
|------|---------|
| C++17 | Core language |
| SFML 3.x | Window, rendering, input, audio |
| MSYS2 / UCRT64 | Compiler toolchain on Windows |
| VS Code | Development environment |

---
