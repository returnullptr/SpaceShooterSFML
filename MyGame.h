#ifndef FINALPROJECTSPACESHOOTER_MYGAME_H
#define FINALPROJECTSPACESHOOTER_MYGAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Health.h"
#include "Rock.h"
#include <ctime>

using namespace sf;

class MyGame : public Game {
public:
    MyGame();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void restrictMap();
    void useUltimate();

    void updateControl();
    void updateBullets();
    void updateEnemies();
    void updateHP();
    int getHP();
    void updateScore();
    void updateHealthPacks();
    void updateRocks();
    void updateUltimate();

    virtual void start(sf::RenderWindow& window);
    virtual void addEvents(sf::RenderWindow &window);
    virtual void addEvents(const sf::RenderWindow &window, sf::Event& event);
    virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;
    virtual void exit();

    void pauseGame();
    void continueGame();
    bool isPaused() const;
    bool isVictory() const;
    bool isUltimateReady() const;

    void newRound();
    Music bgm;

protected:
    Texture bulletTexture;
    Texture playerTexture;
    Texture enemyTexture;
    Texture backgroundTexture;
    Texture explosionTexture;
    Texture healthPackTexture;
    Texture rockTexture;
    Texture enemyBulletTexture;
    Texture ultimateTexture;

    Sprite backgroundSprite;
    Sprite ultimateSprite;

    Font gameFont;
    Text scoreCountText;
    Text gameOverText;
    Text playerHPText;
    Text enemyHPText;
    Text gamePausedText;
    Text instructionText;
    Text victoryText;
    Text ultimateNRText;
    Text ultimateReadyText;

    int currentScore;
    int leftShootTimer;
    int rightShootTimer;
    int spawnTimer;
    int healthTimer;
    int rockTimer;
    int enemyShootTimer;
    int ultimateTimer;
    const int victoryScore = 500;

    std::vector<Enemy> enemies;
    std::vector<Explosion> explosions;
    std::vector<Health> healthPacks;
    std::vector<Rock> rocks;

    Player player;

    bool paused;
    bool victory;
    bool ultimateReady;
    bool drawUltimate;
};

#endif //FINALPROJECTSPACESHOOTER_MYGAME_H
