#include "ReturnScreen.h"

ReturnScreen::ReturnScreen() { }
ReturnScreen::ReturnScreen(sf::Window& window, sf::Font& font) {
	sf::Vector2f size(120, 35);
	sf::Vector2f pos(window.getSize().x - size.x - 20, window.getSize().y - size.y - 20);
	addButton("Return To Main", pos, size, font);
}

bool ReturnScreen::getReturn() const { return returnToMain; }
void ReturnScreen::resetReturn() { returnToMain = false; }
void ReturnScreen::clickButton(int buttonID) { returnToMain = true; }