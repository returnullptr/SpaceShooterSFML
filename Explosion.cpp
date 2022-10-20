#include <SFML/Graphics.hpp>
#include "Explosion.h"

using namespace sf;

Explosion::Explosion() {

}

Explosion::Explosion(Texture *texture, Vector2f position) {
    explosionSprite.setTexture(*texture);
    explosionSprite.setScale(0.2f, 0.2f);
    explosionSprite.setPosition(position);
}

Sprite Explosion::getExplosionSprite() {
    return explosionSprite;
}

