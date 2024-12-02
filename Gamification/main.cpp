#include <SFML/Graphics.hpp>
#include <iostream>
#include "IfGame.h"

void RunWindow(sf::RenderWindow&);

int main()
{
    /* Opens a window
     * VideoMode(width, height)
     * string window title */
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Gamification");

    RunWindow(window);

    return 0;
}

void RunWindow(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Could not load font: Arial\n";
        return;
    }

    Screen* currentScreen = nullptr;
    IfGame ifGameScreen(window, font);
    currentScreen = &ifGameScreen;

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
                    currentScreen->update(event, window);
                    break;
                case sf::Event::MouseButtonPressed:
                    currentScreen->update(event, window);
                    break;
                case sf::Event::MouseButtonReleased:
                    currentScreen->update(event, window);
                    break;
            }
        }

        window.clear();
        window.draw(*currentScreen);
        window.display();
    }
}