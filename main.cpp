#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "MyGame.h"

using namespace sf;

int main() {
    bool GAME_STARTED = true;
    sf::RenderWindow window(sf::VideoMode(1920,1080,32),"DaveStation");
    window.setFramerateLimit(60);
    MyGame game;

    game.start(window);
    game.bgm.play();

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();

            }
            //game.addEvents(window, event);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            GAME_STARTED = false;
            window.close();
            game.exit();
        }

        if (Keyboard::isKeyPressed(Keyboard::P))
            game.pauseGame();

        if (game.isUltimateReady()) {
            if (Keyboard::isKeyPressed(Keyboard::Q))
                game.useUltimate();
        }

        if (!game.isPaused()) {
            if (game.getHP() > 0 && !game.isVictory()) {
                if (Keyboard::isKeyPressed(Keyboard::Up))
                    game.moveUp();

                if (Keyboard::isKeyPressed(Keyboard::Down))
                    game.moveDown();

                if (Keyboard::isKeyPressed(Keyboard::Left))
                    game.moveLeft();

                if (Keyboard::isKeyPressed(Keyboard::Right))
                    game.moveRight();

                game.restrictMap();
                game.updateControl();
                game.updateBullets();
                game.updateEnemies();
                game.updateRocks();
                game.updateUltimate();
                game.updateHealthPacks();
                game.updateHP();
                game.updateScore();
            }
            else {
                if (Keyboard::isKeyPressed(Keyboard::R)) {
                    game.newRound();
                }
            }
        }
        else {
            game.bgm.pause();
            if (Keyboard::isKeyPressed(Keyboard::C)) {
                game.bgm.play();
                game.continueGame();
            }
        }

        window.clear(sf::Color::Black);

        if(GAME_STARTED) {
            window.draw(game);
            game.addEvents(window);
            //window.draw(game.getThumbnail());
            //window.draw(game.getInfo(window));
        }
        window.display();
    }
    return 0;
}