#ifndef FINALPROJECTSPACESHOOTER_ROCK_H
#define FINALPROJECTSPACESHOOTER_ROCK_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Rock {
public:
    Rock();
    Rock(Texture *texture, float windowWidth, float windowHeight);
    Sprite getRockSprite() const;
    Vector2f getRockPosition() const ;
    FloatRect getRockBounds() const ;
    void rockMoving(float x, float y);

protected:
    Sprite rockSprite;
};

#endif //FINALPROJECTSPACESHOOTER_ROCK_H
