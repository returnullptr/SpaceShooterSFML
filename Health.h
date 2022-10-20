#ifndef FINALPROJECTSPACESHOOTER_HEALTH_H
#define FINALPROJECTSPACESHOOTER_HEALTH_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Health {
public:
    Health();
    Health(Texture *texture, float windowWidth, float windowHeight);
    Sprite getHealthSprite() const;
    void healthPackMoving(float x, float y);
    Vector2f getHealthPosition() const;
    FloatRect getHealthBounds() const;

protected:
    Sprite healthSprite;
};

#endif //FINALPROJECTSPACESHOOTER_HEALTH_H
