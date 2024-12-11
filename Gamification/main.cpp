#include <SFML/Graphics.hpp>
#include <iostream>
#include "ReturnScreen.h"
#include "MainScreen.h"
#include "IfGame.h"
#include "Logger.h"

void RunWindow(sf::RenderWindow&);

int main()
{
    /* Opens a window
     * VideoMode(width, height)
     * string window title */
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Gamification");
    Logger::init();

    RunWindow(window);

    return 0;
}

void RunWindow(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        Logger::log("Could not load font: Arial\n");
        return;
    }

    Screen* currentScreen = nullptr;
    ReturnScreen returnScreen(window, font);
    MainScreen mainScreen(window, font);
    IfGame ifGameScreen(window, font);
    currentScreen = &mainScreen;
    mainScreen.setActive(true);

    sf::Clock clock;
    window.setFramerateLimit(60);

    
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        currentScreen->update(deltaTime.asSeconds(), window);
        /* Polls for all of the window's events that were triggered since the last iteration of the loop
         * Necessary for the window to be responsive and should be done at the beginning of the loop */
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                    currentScreen->update(event, window);
                    returnScreen.update(event, window);
                    break;
            }
        }

        // Leave main screen and go to mini game screen
        if (mainScreen.getActive()) {
            switch (mainScreen.getGameIndex())
            {
                default:
                    break;
                case 0:
                    mainScreen.setActive(false);
                    mainScreen.resetGameIndex();
                    currentScreen = &ifGameScreen;
                    ifGameScreen.init();
                    ifGameScreen.setActive(true);
                    returnScreen.setActive(true);
                    break;
                // More cases can be added when more minigames are added
            }
        }

        // Leave mini game and return to the main screen
        if (returnScreen.getReturn()) {
            currentScreen->setActive(false);
            currentScreen = &mainScreen;
            mainScreen.setActive(true);
            returnScreen.setActive(false);
            returnScreen.resetReturn();
        }

        window.clear();
        window.draw(*currentScreen);
        window.draw(returnScreen);
        window.display();
    }
}