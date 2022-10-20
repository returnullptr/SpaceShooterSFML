#ifndef FINALPROJECTSPACESHOOTER_ENEMYBULLET_H
#define FINALPROJECTSPACESHOOTER_ENEMYBULLET_H

#include <SFML/Graphics.hpp>

using namespace sf;

class EnemyBullet {
public:
    EnemyBullet();
    EnemyBullet(Texture *texture, float x, float y);
    void enemyBulletMoving(float x, float y);
    Vector2f getEnemyBulletPosition() const;
    FloatRect getEnemyBulletBounds() const;
    Sprite getEnemyBulletSprite() const;

protected:
    Sprite enemyBulletSprite;
};

#endif //FINALPROJECTSPACESHOOTER_ENEMYBULLET_H
