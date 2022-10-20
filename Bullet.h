#ifndef FINALPROJECTSPACESHOOTER_BULLET_H
#define FINALPROJECTSPACESHOOTER_BULLET_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
public:
    Bullet();
    // left bullet
    Bullet(Texture *texture, Vector2f position);
    // right bullet
    Bullet(Texture *texture, float x, float y);

    void leftBulletMoving(float x, float y);
    Vector2f getLeftBulletPosition() const;
    FloatRect getLeftBulletBounds() const;
    Sprite getLeftBulletSprite() const;

    void rightBulletMoving(float x, float y);
    Vector2f getRightBulletPosition() const;
    FloatRect getRightBulletBounds() const;
    Sprite getRightBulletSprite() const;

protected:
    Sprite leftBulletSprite;
    Sprite rightBulletSprite;

};

#endif //FINALPROJECTSPACESHOOTER_BULLET_H
