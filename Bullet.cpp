#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

using namespace sf;

Bullet::Bullet() {

}

Bullet::Bullet(Texture *texture, Vector2f position) {
    leftBulletSprite.setTexture(*texture);
    leftBulletSprite.setScale(0.2f, 0.2f);
    leftBulletSprite.setPosition(position);
}

Bullet::Bullet(Texture *texture, float x, float y) {
    rightBulletSprite.setTexture(*texture);
    rightBulletSprite.setScale(0.2f, 0.2f);
    rightBulletSprite.setPosition(x, y);
}

void Bullet::leftBulletMoving(float x, float y) {
    leftBulletSprite.move(x, y);
}

Vector2f Bullet::getLeftBulletPosition() const{
    return leftBulletSprite.getPosition();
}

FloatRect Bullet::getLeftBulletBounds() const {
    return leftBulletSprite.getGlobalBounds();
}

Sprite Bullet::getLeftBulletSprite() const {
    return leftBulletSprite;
}

void Bullet::rightBulletMoving(float x, float y) {
    rightBulletSprite.move(x, y);
}

Vector2f Bullet::getRightBulletPosition() const {
    return rightBulletSprite.getPosition();
}

FloatRect Bullet::getRightBulletBounds() const {
    return rightBulletSprite.getGlobalBounds();
}

Sprite Bullet::getRightBulletSprite() const {
    return rightBulletSprite;
}