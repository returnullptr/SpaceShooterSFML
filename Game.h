//
// Created by Dave R. Smith on 10/25/19.
//

#ifndef TEST_STATIC_GAME_H
#define TEST_STATIC_GAME_H
#include <string>
#include <list>
//#include "Game_Interface.h"
#include <SFML/Graphics.hpp>
#include "Thumbnail.h"
#include "GameText.h"
#include <fstream>
using std::string;

class Game :  public sf::Transformable, public sf::Drawable {
public:
    Game();
    void load_game();

    sf::RectangleShape* getSfThumbnail();
    Thumbnail getThumbnail();
    string getTitle();
    std::string getImagePath();
    GameText getInfo(sf::RenderWindow &window);

    /*
    virtual void start(sf::RenderWindow& window) = 0;
    virtual void addEvents(sf::RenderWindow &window) = 0;
    virtual void addEvents(const sf::RenderWindow &window, sf::Event& event) = 0;
    virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const = 0;*/
    virtual void exit() = 0;

private:
    //static std::map<std::string, const Game&> LOAD_GAME;
    void setThumbnail();
    Thumbnail thumbnail;

protected:
    void init();
    string image_path;
    string info_path;
    string title;
};


#endif //TEST_STATIC_GAME_H
