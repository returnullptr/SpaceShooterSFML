#include <SFML/Graphics.hpp>
#include "Enemy.h"

using namespace sf;

Enemy::Enemy() {

}

Enemy::Enemy(Texture *texture, int windowWidth, int windowHeight) {
    maxHP = rand() % 3 + 1;
    currentHP = maxHP;

    enemySprite.setTexture(*texture);
    enemySprite.setScale(0.08f, 0.08f);
    // enemy spawn at top of window
    enemySprite.setPosition(rand() % (int)(windowWidth - enemySprite.getGlobalBounds().width),
                            0 - enemySprite.getGlobalBounds().height);
}

void Enemy::enemyMoving(float x, float y) {
    enemySprite.move(x, y);
}

Vector2f Enemy::getEnemyPosition() const {
    return enemySprite.getPosition();
}

FloatRect Enemy::getEnemyBounds() const {
    return enemySprite.getGlobalBounds();
}

Sprite Enemy::getEnemySprite() const {
    return enemySprite;
}

int Enemy::getEnemyMaxHP() const {
    return maxHP;
}



