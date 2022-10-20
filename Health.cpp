#include <SFML/Graphics.hpp>
#include "Health.h"

using namespace sf;

Health::Health() {

}

Health::Health(Texture *texture, float windowWidth, float windowHeight) {
    healthSprite.setTexture(*texture);
    healthSprite.setScale(0.1f, 0.1f);

    healthSprite.setPosition(rand() % (int) (windowWidth - healthSprite.getGlobalBounds().width),
                             0 - healthSprite.getGlobalBounds().height);
}

Sprite Health::getHealthSprite() const {
    return healthSprite;
}

void Health::healthPackMoving(float x, float y) {
    healthSprite.move(x, y);
}

Vector2f Health::getHealthPosition() const {
    return healthSprite.getPosition();
}

FloatRect Health::getHealthBounds() const {
    return healthSprite.getGlobalBounds();
}
