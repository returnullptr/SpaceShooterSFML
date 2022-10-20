#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "MyGame.h"

using namespace sf;

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

MyGame::MyGame() {
    image_path = "images/thumbnail.jpg";
    if(!bulletTexture.loadFromFile("images/bullet.png")) {
        std::cout << "Error loading textures" << std::endl;
    }
    playerTexture.loadFromFile("images/playerShip.png");
    enemyTexture.loadFromFile("images/enemyShip.png");
    backgroundTexture.loadFromFile("images/spaceBackground.png");
    explosionTexture.loadFromFile("images/explosion.png");
    healthPackTexture.loadFromFile("images/health.png");
    rockTexture.loadFromFile("images/rock.png");
    enemyBulletTexture.loadFromFile("images/enemyBullet.png");
    ultimateTexture.loadFromFile("images/ultTexture.png");
    if (!gameFont.loadFromFile("OpenSans-Bold.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    scoreCountText.setFont(gameFont);
    gameOverText.setFont(gameFont);
    playerHPText.setFont(gameFont);
    enemyHPText.setFont(gameFont);
    gamePausedText.setFont(gameFont);
    instructionText.setFont(gameFont);
    victoryText.setFont(gameFont);
    ultimateNRText.setFont(gameFont);
    ultimateReadyText.setFont(gameFont);

    if(!bgm.openFromFile("bgm/gameBGM.ogg"))
        std::cout << "Error loading music" << std::endl;
    bgm.setLoop(true);
    bgm.setVolume(30);

    title = "Space Shooter";
}

void MyGame::moveUp() {
    player.moveUp();
}

void MyGame::moveDown() {
    player.moveDown();
}

void MyGame::moveLeft() {
    player.moveLeft();
}

void MyGame::moveRight() {
    player.moveRight();
}

void MyGame::start(sf::RenderWindow& window) {
    // init scoreText
    scoreCountText.setCharacterSize(16);
    scoreCountText.setFillColor(Color::White);
    scoreCountText.setPosition(1800.f, 10.f);
    scoreCountText.setOutlineThickness(3.f);

    // init gameOverText
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(WINDOW_WIDTH/2.0f - 180.f, WINDOW_HEIGHT/2.0f - 40.f);
    gameOverText.setString("GAME OVER");

    // init gamePausedText
    gamePausedText.setCharacterSize(60);
    gamePausedText.setFillColor(Color::Yellow);
    gamePausedText.setPosition(WINDOW_WIDTH/2.0f - 180.f, WINDOW_HEIGHT/2.0f - 40.f);
    gamePausedText.setString("GAME PAUSED");

    // init victoryText
    victoryText.setCharacterSize(60);
    victoryText.setFillColor(Color::Green);
    victoryText.setPosition(WINDOW_WIDTH/2.0f - 160.f, WINDOW_HEIGHT/2.0f - 40.f);
    victoryText.setString("VICTORY");

    // init playerHPText
    playerHPText.setCharacterSize(16);
    playerHPText.setFillColor(Color::Green);
    playerHPText.setPosition(10.f, 10.f);
    scoreCountText.setOutlineThickness(3.f);

    // init enemyHPText
    enemyHPText.setCharacterSize(10);
    enemyHPText.setFillColor(Color::Red);

    // init instructionText
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(Color::White);
    instructionText.setPosition(10.f, WINDOW_HEIGHT/2.0f - 40.f);
    instructionText.setString("Shoot: SPACE\nUltimate: Q\nPause: P\nContinue: C\nPlay Again: R");

    // init ultimateText
    ultimateNRText.setCharacterSize(16);
    ultimateNRText.setFillColor(Color::White);
    ultimateNRText.setPosition(10.f, 30.f);
    ultimateNRText.setString("Ultimate: Not Ready");
    ultimateNRText.setOutlineThickness(1.f);

    ultimateReadyText.setCharacterSize(16);
    ultimateReadyText.setFillColor(Color::Blue);
    ultimateReadyText.setPosition(10.f, 30.f);
    ultimateReadyText.setString("Ultimate: Ready");
    ultimateReadyText.setOutlineThickness(1.f);

    // init variables
    currentScore = 0;
    leftShootTimer = 0;
    rightShootTimer = 0;
    spawnTimer = 0;
    healthTimer = 0;
    rockTimer = 0;
    enemyShootTimer = 0;
    ultimateTimer = 0;

    // call Player constructor
    player = Player(&playerTexture);
    player.setPlayerPosition((WINDOW_WIDTH - player.getPlayerBounds().width)/2.f, WINDOW_HEIGHT/2.f);

    // init sprite
    backgroundSprite.setTexture(backgroundTexture);
    ultimateSprite.setTexture(ultimateTexture);
    ultimateSprite.setPosition((WINDOW_WIDTH - ultimateSprite.getLocalBounds().width)/2.f,
                               (WINDOW_HEIGHT - ultimateSprite.getLocalBounds().height)/2.f);

    // init state booleans
    paused = false;
    victory = false;
    ultimateReady = false;
    drawUltimate = false;
}

void MyGame::restrictMap() {
    // out of top
    if (player.getPlayerPosition().y <= 0)
        player.setPlayerPosition(player.getPlayerPosition().x, 0.f);
    // out of bottom
    if (player.getPlayerPosition().y >= WINDOW_HEIGHT - player.getPlayerBounds().height)
        player.setPlayerPosition(player.getPlayerPosition().x, WINDOW_HEIGHT - player.getPlayerBounds().height);
    // out of left
    if (player.getPlayerPosition().x <= 0)
        player.setPlayerPosition(0.f, player.getPlayerPosition().y);
    // out of right
    if (player.getPlayerPosition().x >= WINDOW_WIDTH - player.getPlayerBounds().width)
        player.setPlayerPosition(WINDOW_WIDTH - player.getPlayerBounds().width, player.getPlayerPosition().y);
}

void MyGame::updateControl() {
    if (leftShootTimer < 5)
        leftShootTimer++;

    else if (Keyboard::isKeyPressed(Keyboard::Space) && leftShootTimer >= 5) {
        // create left bullet
        player.leftBullets.push_back(Bullet(&bulletTexture, player.getPlayerPosition()));

        leftShootTimer = 0;
    }

    if (rightShootTimer < 5)
        rightShootTimer++;

    else if (Keyboard::isKeyPressed(Keyboard::Space) && rightShootTimer >= 5) {
        // create right bullet
        float playerPositionX = player.getPlayerPosition().x;
        float playerPositionY = player.getPlayerPosition().y;
        playerPositionX += 40.f;
        player.rightBullets.push_back(Bullet(&bulletTexture, playerPositionX, playerPositionY));

        rightShootTimer = 0;
    }

    // enemy shoot settings
    if (enemyShootTimer < 50)
        enemyShootTimer++;

    else if (enemyShootTimer >= 50) {
        // create enemy bullet
        for (int i = 0; i < enemies.size(); i++) {
            float enemyPositionX = enemies[i].getEnemyPosition().x;
            float enemyPositionY = enemies[i].getEnemyPosition().y;
            enemyPositionX += 12.f;
            enemyPositionY -= 8.f;
            enemies[i].enemyBullets.push_back(EnemyBullet(&bulletTexture, enemyPositionX, enemyPositionY));

            enemyShootTimer = 0;
        }
    }
}

void MyGame::updateBullets() {
    // left bullets move upwards
    for (int i = 0; i < player.leftBullets.size(); i++) {
        player.leftBullets[i].leftBulletMoving(0.f, -20.f);
        // delete bullet if out of top bezel
        if (player.leftBullets[i].getLeftBulletPosition().y < 0) {
            player.leftBullets.erase(player.leftBullets.begin() + i);
            break;
        }

        // when bullet collide with enemy
        for (int j = 0; j < enemies.size(); j++) {
            if (player.leftBullets[i].getLeftBulletBounds().intersects(enemies[j].getEnemyBounds())) {
                if (enemies[j].currentHP <= 1) {
                    currentScore += 2;
                    explosions.push_back(Explosion(&explosionTexture, enemies[j].getEnemyPosition()));
                    enemies.erase(enemies.begin() + j);
                }
                else {
                    enemies[j].currentHP--;
                }

                // delete hit bullets
                player.leftBullets.erase(player.leftBullets.begin() + i);
                break;
            }
        }

        // when bullet collide with rock
        for (int k = 0; k < rocks.size(); k++) {
            if (player.leftBullets[i].getLeftBulletBounds().intersects(rocks[k].getRockBounds())) {
                currentScore++;
                explosions.push_back(Explosion(&explosionTexture, rocks[k].getRockPosition()));
                rocks.erase(rocks.begin() + k);

                player.leftBullets.erase(player.leftBullets.begin() + i);
                break;
            }
        }
    }

    // right bullets move upwards
    for (int i = 0; i < player.rightBullets.size(); i++) {
        player.rightBullets[i].rightBulletMoving(0.f, -20.f);

        // delete bullet if out of top bezel
        if (player.rightBullets[i].getRightBulletPosition().y < 0) {
            player.rightBullets.erase(player.rightBullets.begin() + i);
            break;
        }

        // when bullet collide with enemy
        for (int j = 0; j < enemies.size(); j++) {
            if (player.rightBullets[i].getRightBulletBounds().intersects(enemies[j].getEnemyBounds())) {
                if (enemies[j].currentHP <= 1) {
                    currentScore += 2;
                    explosions.push_back(Explosion(&explosionTexture, enemies[j].getEnemyPosition()));
                    enemies.erase(enemies.begin() + j);
                }
                else {
                    enemies[j].currentHP--;
                }

                // delete hit bullets
                player.rightBullets.erase(player.rightBullets.begin() + i);
                break;
            }
        }

        for (int k = 0; k < rocks.size(); k++) {
            if (player.rightBullets[i].getRightBulletBounds().intersects(rocks[k].getRockBounds())) {
                currentScore++;
                explosions.push_back(Explosion(&explosionTexture, rocks[k].getRockPosition()));
                rocks.erase(rocks.begin() + k);

                player.rightBullets.erase(player.rightBullets.begin() + i);
                break;
            }
        }
    }

    // enemy bullets
    for (int i = 0; i < enemies.size(); i++) {
        for (int j = 0; j < enemies[i].enemyBullets.size(); j++) {
            enemies[i].enemyBullets[j].enemyBulletMoving(0.f, 10.f);

            // delete bullet if out of bottom bezel
            if (enemies[i].enemyBullets[j].getEnemyBulletPosition().y > WINDOW_HEIGHT) {
                enemies[i].enemyBullets.erase(enemies[i].enemyBullets.begin() + j);
                break;
            }

            // when bullet collide with player
            if (enemies[i].enemyBullets[j].getEnemyBulletBounds().intersects(player.getPlayerBounds())) {
                explosions.push_back(Explosion(&explosionTexture, player.getPlayerPosition()));
                player.currentHP--;

                // delete hit bullets
                enemies[i].enemyBullets.erase(enemies[i].enemyBullets.begin() + j);
                break;
            }
        }
    }
}

void MyGame::updateEnemies() {
    // in between spawns
    if (spawnTimer < 100)
        spawnTimer++;

    // spawn new enemy
    if (spawnTimer >= 100) {
        enemies.push_back(Enemy(&enemyTexture, WINDOW_WIDTH, WINDOW_HEIGHT));
        spawnTimer = 0;
    }

    // enemy move downwards
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].enemyMoving(0.f, rand()%1+0.5);

        // out of bottom
        if (enemies[i].getEnemyPosition().y >= WINDOW_HEIGHT + enemies[i].getEnemyBounds().height) {
            enemies.erase(enemies.begin() + i);
            player.currentHP -= 2;
            break;
        }

        // when enemy collide with player
        if (enemies[i].getEnemyBounds().intersects(player.getPlayerBounds())) {
            explosions.push_back(Explosion(&explosionTexture, enemies[i].getEnemyPosition()));
            enemies.erase(enemies.begin() + i);
            player.currentHP -= 2;
            currentScore++;
            break;
        }
    }
}

void MyGame::updateHP() {
    playerHPText.setString("HP: " + std::to_string(player.currentHP) + "/" + std::to_string(player.getMaxHP()));
}

int MyGame::getHP() {
    return player.currentHP;
}

void MyGame::updateScore() {
    scoreCountText.setString("Score: " + std::to_string(currentScore) + "/500");
    if (currentScore >= victoryScore)
        victory = true;
}

void MyGame::updateHealthPacks() {
    if (healthTimer < 1500)
        healthTimer++;

    if (healthTimer >= 1500) {
        healthPacks.push_back(Health(&healthPackTexture, WINDOW_WIDTH, WINDOW_HEIGHT));
        healthTimer = 0;
    }

    for (int i = 0; i < healthPacks.size(); i++) {
        healthPacks[i].healthPackMoving(0.f, 2.f);

        // health pack out of bottom
        if (healthPacks[i].getHealthPosition().y >= WINDOW_HEIGHT + healthPacks[i].getHealthBounds().height) {
            healthPacks.erase(healthPacks.begin() + i);
            break;
        }

        // when player collide with health pack
        if (healthPacks[i].getHealthBounds().intersects(player.getPlayerBounds())) {
            healthPacks.erase(healthPacks.begin() + i);
            if (player.currentHP < player.getMaxHP()) {
                if (player.currentHP > 15) {
                    player.currentHP += (player.getMaxHP() - player.currentHP);
                }
                else
                    player.currentHP += 5;
            }
            break;
        }
    }
}

void MyGame::updateRocks() {
    if (rockTimer < 25)
        rockTimer++;

    if (rockTimer >= 25) {
        rocks.push_back(Rock(&rockTexture, WINDOW_WIDTH, WINDOW_HEIGHT));
        rockTimer = 0;
    }

    for (int i = 0; i < rocks.size(); i++) {
        rocks[i].rockMoving(0.f, 0.8);

        // rock out of bottom
        if (rocks[i].getRockPosition().y >= WINDOW_HEIGHT + rocks[i].getRockBounds().height) {
            rocks.erase(rocks.begin() + i);
            player.currentHP--;
            break;
        }

        // when rock collide with player
        if (rocks[i].getRockBounds().intersects(player.getPlayerBounds())) {
            explosions.push_back(Explosion(&explosionTexture, rocks[i].getRockPosition()));
            rocks.erase(rocks.begin() + i);
            player.currentHP--;
            currentScore++;
            break;
        }
    }
}

void MyGame::updateUltimate() {
    if (ultimateTimer < 3000)
        ultimateTimer++;

    else if (ultimateTimer >= 3000)
        ultimateReady = true;
}

void MyGame::useUltimate() {
    // 1 point per unit destroyed
    int temp = 0;
    for (int i = 0; i < enemies.size(); i++) {
        temp++;
    }
    for (int i = 0; i < rocks.size(); i++) {
        temp++;
    }
    currentScore += temp;

    // wipe all enemies and bullets
    enemies.clear();
    rocks.clear();
    for (int i = 0; i < enemies.size(); i++)
        enemies[i].enemyBullets.clear();

    ultimateReady = false;
    ultimateTimer = 0;
    drawUltimate = true;
}

void MyGame::addEvents(sf::RenderWindow &window) {
    // draw enemy sprite
    for (int i = 0; i < enemies.size(); i++) {
        enemyHPText.setString(std::to_string(enemies[i].currentHP) + "/" + std::to_string(enemies[i].getEnemyMaxHP()));
        enemyHPText.setPosition(enemies[i].getEnemyPosition().x + 8.f,
                                enemies[i].getEnemyPosition().y - enemyHPText.getGlobalBounds().height - 3.f);
        window.draw(enemies[i].getEnemySprite());
        window.draw(enemyHPText);
    }

    // draw rock sprite
    for (int i = 0; i < rocks.size(); i++) {
        window.draw(rocks[i].getRockSprite());
    }

    // draw explosion sprite
    for (int i = 0; i < explosions.size(); i++) {
        window.draw(explosions[i].getExplosionSprite());
    }
    // delete explosions
    for (int i = 0; i < explosions.size(); i++) {
        explosions.erase(explosions.begin());
    }

    // draw ultimate text
    if (!ultimateReady)
        window.draw(ultimateNRText);
    else if (ultimateReady)
        window.draw(ultimateReadyText);

    // draw ultimate
    if (drawUltimate) {
        window.draw(ultimateSprite);
        drawUltimate = false;
    }
}

void MyGame::addEvents(const sf::RenderWindow &window, sf::Event &event) {

}

void MyGame::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    window.draw(backgroundSprite);

    // draw player sprite
    window.draw(player.getPlayerSprite());

    // draw left bullets sprite
    for (int i = 0; i < player.leftBullets.size(); i++)
        window.draw(player.leftBullets[i].getLeftBulletSprite());

    // draw right bullets sprite
    for (int i = 0; i < player.rightBullets.size(); i++) {
        window.draw(player.rightBullets[i].getRightBulletSprite());
    }

    // draw enemy bullets sprite
    for (int i = 0; i < enemies.size(); i++) {
        for (int j = 0; j < enemies[i].enemyBullets.size(); j++) {
            window.draw(enemies[i].enemyBullets[j].getEnemyBulletSprite());
        }
    }

    for (int i = 0; i < healthPacks.size(); i++) {
        window.draw(healthPacks[i].getHealthSprite());
    }

    window.draw(scoreCountText);
    window.draw(playerHPText);
    window.draw(instructionText);

    if (player.currentHP <= 0)
        window.draw(gameOverText);

    if (isPaused())
        window.draw(gamePausedText);

    if (isVictory())
        window.draw(victoryText);

}

void MyGame::exit() {
    std::exit(0);
}

void MyGame::pauseGame() {
    paused = true;
}

void MyGame::continueGame() {
    paused = false;
}

bool MyGame::isPaused() const{
    return paused;
}

void MyGame::newRound() {
    player.currentHP = player.getMaxHP();
    currentScore = 0;
    victory = false;
    healthTimer = 0;
    ultimateReady = false;
    ultimateTimer = 0;

    // delete all enemies
    enemies.clear();

    // delete all rocks
    rocks.clear();

    // delete all bullets
    player.leftBullets.clear();
    player.rightBullets.clear();

    for (int i = 0; i < enemies.size(); i++)
        enemies[i].enemyBullets.clear();

    // delete all health packs
    healthPacks.clear();

    // player position reset to center
    player.setPlayerPosition(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);
}

bool MyGame::isVictory() const {
    return victory;
}

bool MyGame::isUltimateReady() const {
    return ultimateReady;
}



