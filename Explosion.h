#ifndef FINALPROJECTSPACESHOOTER_EXPLOSION_H
#define FINALPROJECTSPACESHOOTER_EXPLOSION_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Explosion {
public:
    Explosion();
    Explosion(Texture *texture, Vector2f position);
    Sprite getExplosionSprite();

protected:
    Sprite explosionSprite;
};

#endif //FINALPROJECTSPACESHOOTER_EXPLOSION_H
