#include <SFML/Graphics.hpp>
#include "Rock.h"

using namespace sf;

Rock::Rock() {

}

Rock::Rock(Texture *texture, float windowWidth, float windowHeight) {
    rockSprite.setTexture(*texture);
    rockSprite.setScale(0.1f, 0.1f);
    rockSprite.setPosition(rand() % (int) (windowWidth - rockSprite.getGlobalBounds().width),
                           0 - rockSprite.getGlobalBounds().height);
}

Sprite Rock::getRockSprite() const {
    return rockSprite;
}

Vector2f Rock::getRockPosition() const {
    return rockSprite.getPosition();
}

FloatRect Rock::getRockBounds() const {
    return rockSprite.getGlobalBounds();
}

void Rock::rockMoving(float x, float y) {
    rockSprite.move(x, y);
}
