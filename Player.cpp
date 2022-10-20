#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"

using namespace sf;

Player::Player() {

}

Player::Player(Texture *texture) {
    maxHP = 20;
    currentHP = maxHP;

    playerSprite.setTexture(*texture);
    playerSprite.setScale(0.1f, 0.1f);
}

void Player::moveUp() {
    playerSprite.move(0.f, -10.f);
}

void Player::moveDown() {
    playerSprite.move(0.f, 10.f);
}

void Player::moveRight() {
    playerSprite.move(10.f, 0.f);
}

void Player::moveLeft() {
    playerSprite.move(-10.f, 0.f);
}

Sprite Player::getPlayerSprite() const {
    return playerSprite;
}

Vector2f Player::getPlayerPosition() const {
    return playerSprite.getPosition();
}

Vector2f Player::setPlayerPosition(float x, float y) {
    playerSprite.setPosition(x, y);
}

FloatRect Player::getPlayerBounds() const {
    return playerSprite.getGlobalBounds();
}

int Player::getCurrentHP() {
    return currentHP;
}

int Player::getMaxHP() {
    return maxHP;
}