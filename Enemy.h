#ifndef FINALPROJECTSPACESHOOTER_ENEMY_H
#define FINALPROJECTSPACESHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>
#include "EnemyBullet.h"

using namespace sf;

class Enemy : public EnemyBullet{
public:
    Enemy();
    Enemy(Texture *texture, int windowWidth, int windowHeight);

    void enemyMoving(float x, float y);
    Vector2f getEnemyPosition() const;
    FloatRect getEnemyBounds() const;
    Sprite getEnemySprite() const;
    int getEnemyMaxHP() const;

    int currentHP;

    std::vector<EnemyBullet> enemyBullets;

protected:
    Sprite enemySprite;

    int maxHP;
};

#endif //FINALPROJECTSPACESHOOTER_ENEMY_H
