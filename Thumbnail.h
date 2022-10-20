//
// Created by Dave R. Smith on 10/26/19.
//

#ifndef SFML_THUMBNAIL_H
#define SFML_THUMBNAIL_H
#include <SFML/Graphics.hpp>
#include <string>
#include "GameText.h"

class Thumbnail : public sf::Transformable, public sf::Drawable{
public:
    Thumbnail();
    Thumbnail(std::string basicString, std::string title,
            sf::Rect<float> rect, const sf::Vector2u vector2);
    //~Thumbnail();

    std::string getImagePath();
    sf::RectangleShape* getThumbnail();
    sf::Texture* getTexture();

    void setSelected(bool choice);
    bool getSelected();

    void initialize();
    void setWindowSize(sf::Vector2<unsigned int> windowSize);
    void setLeftMargin(sf::Rect<float>& margin);

    GameText getTitle();
    void highlightThumbnail();
    void unhighlightThumbnail();

    virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;

private:
    sf::RectangleShape *sprite;
    sf::Texture *texture = nullptr;

    bool loaded;
    bool isThumbnailLoaded();
    static bool firstThumbnail;
    bool selected = false;

    static float x;
    static float y;
    float padding = 50.f;

    void setThumbnail();
    void setPosition();
    void setFrame();

    sf::Vector2f windowSize;
    sf::Rect<float> leftMargin;
    std::string image_path;
    GameText title;
    sf::Vector2f titlePosition;
};


#endif //SFML_THUMBNAIL_H
