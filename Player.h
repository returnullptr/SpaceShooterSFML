#ifndef FINALPROJECTSPACESHOOTER_PLAYER_H
#define FINALPROJECTSPACESHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

using namespace sf;

class Player : public Bullet{
public:
    Player();
    Player(Texture *texture);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    Sprite getPlayerSprite() const;
    Vector2f getPlayerPosition() const;
    Vector2f setPlayerPosition(float x, float y);
    FloatRect getPlayerBounds() const;

    int getCurrentHP();
    int getMaxHP();

    std::vector<Bullet> leftBullets;
    std::vector<Bullet> rightBullets;

    int currentHP;

protected:
    Sprite playerSprite;

    int maxHP;
};

#endif //FINALPROJECTSPACESHOOTER_PLAYER_H
