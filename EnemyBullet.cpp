#include <SFML/Graphics.hpp>
#include "EnemyBullet.h"

using namespace sf;

EnemyBullet::EnemyBullet() {

}

EnemyBullet::EnemyBullet(Texture *texture, float x, float y) {
    enemyBulletSprite.setTexture(*texture);
    enemyBulletSprite.setScale(0.1f, 0.1f);
    enemyBulletSprite.setPosition(x, y);
}

void EnemyBullet::enemyBulletMoving(float x, float y) {
    enemyBulletSprite.move(x, y);
}

Vector2f EnemyBullet::getEnemyBulletPosition() const {
    return enemyBulletSprite.getPosition();
}

FloatRect EnemyBullet::getEnemyBulletBounds() const {
    return enemyBulletSprite.getGlobalBounds();
}

Sprite EnemyBullet::getEnemyBulletSprite() const {
    return enemyBulletSprite;
}


