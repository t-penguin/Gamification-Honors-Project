#include "Screen.h"

sf::Color Screen::blue = sf::Color(31, 99, 185);			// #1F63B9
sf::Color Screen::yellow = sf::Color(238, 171, 66);			// #DEAB42
sf::Color Screen::green = sf::Color(128, 174, 54);			// #80AE36
sf::Color Screen::red = sf::Color(254, 44, 47);				// #FE2C2F
sf::Color Screen::containerGray = sf::Color(20, 20, 20);	// #141414



/* Destructor */

Screen::~Screen() {
	
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
void Screen::addContainer(const sf::Vector2f& size, const sf::Vector2f& pos) { containers.emplace_back(this, size, pos); }


/* Public virtual functions */

void Screen::update(sf::Event& e, sf::RenderWindow& window) {
	for (Button& b : buttons)
		b.update(e, window);

	for (Container& c : containers)
		c.update(e, window);
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const Container& c : containers)
		c.draw(target, states);
	
	for (const sf::Sprite& sp : sprites)
		target.draw(sp, states);

	for (const Button& b : buttons)
		b.draw(target, states);

	for (const sf::Text& t : texts)
		target.draw(t, states);
}