#include "Screen.h"

/* Constructor */

Screen::Screen() {
	yellow = sf::Color(238, 171, 66);
	green = sf::Color(128, 174, 54);
	red = sf::Color(254, 44, 47);
}


/* Destructor */

Screen::~Screen() {
	for (int i = 0; i < shapes.size(); i++)
		delete shapes.at(i);
}


/* Protected helper functions */

void Screen::addButton(std::string str, sf::Vector2f position, sf::Vector2f size, sf::Font& font, unsigned int fontSize) { 
	buttons.emplace_back(this, buttons.size(), str, position, size, font, fontSize);
}

void Screen::addText(std::string str, sf::Font& font, unsigned int fontSize) {
	texts.emplace_back(str, font, fontSize);
}

void Screen::addSprite() { sprites.emplace_back(); }
void Screen::addSprite(sf::Texture& texture) { sprites.emplace_back(texture); }
void Screen::addShape(sf::Shape* shape) { shapes.push_back(shape); }


/* Public virtual functions */

void Screen::update(sf::Event& e, sf::RenderWindow& window) {
	for (Button& b : buttons)
		b.update(e, window);
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const sf::Shape* sh : shapes)
		target.draw(*sh, states);
	
	for (const sf::Sprite& sp : sprites)
		target.draw(sp, states);

	for (const Button& b : buttons)
		b.draw(target, states);

	for (const sf::Text& t : texts)
		target.draw(t, states);
}