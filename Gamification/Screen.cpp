#include "Screen.h"

Screen::Screen() {
	yellow = sf::Color(238, 171, 66);
	green = sf::Color(128, 174, 54);
	red = sf::Color(254, 44, 47);
}

// Releases the memory held by the shapes vector
Screen::~Screen() {
	for (int i = 0; i < shapes.size(); i++)
		delete shapes.at(i);
}

// Returns the pointer to the item in its list at the given index
Button* Screen::getButtonAt(int index) const { return (Button*)&(buttons.at(index)); }
sf::Text* Screen::getTextAt(int index) const { return (sf::Text*)&(texts.at(index)); }
sf::Shape* Screen::getShapeAt(int index) const { return shapes.at(index); }

// Adds an to the end of its given list
void Screen::addButton(Button button) { buttons.push_back(button); }
void Screen::addText(sf::Text text) { texts.push_back(text); }
void Screen::addSprite(sf::Sprite sprite) { sprites.push_back(sprite); }
void Screen::addShape(sf::Shape* shape) { shapes.push_back(shape); }

// Removes an item from its given list at the given index
void Screen::removeButtonAt(int index) { buttons.erase(buttons.begin() + index); }
void Screen::removeTextAt(int index) { texts.erase(texts.begin() + index); }
void Screen::removeShapeAt(int index) { shapes.erase(shapes.begin() + index); } // Free memory as well

// Sends update events to screen elements
void Screen::update(sf::Event& e, sf::RenderWindow& window) {
	for (int i = 0; i < buttons.size(); i++)
		buttons.at(i).update(e, window);
}

// Draws all the elements on the screen
void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int i = 0; i < shapes.size(); i++)
		target.draw(*(shapes.at(i)), states);

	for (int i = 0; i < sprites.size(); i++)
		target.draw(sprites.at(i), states);
	
	for (int i = 0; i < buttons.size(); i++)
		buttons.at(i).draw(target, states);

	for (int i = 0; i < texts.size(); i++)
		target.draw(texts.at(i), states);
}