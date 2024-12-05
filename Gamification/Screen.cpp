#include "Screen.h"

sf::Color Screen::defaultBorder = sf::Color(230, 159, 0);	// #E69F00
sf::Color Screen::trueColor = sf::Color(0, 90, 181);		// #005AB5
sf::Color Screen::falseColor = sf::Color(220, 50, 32);		// #DC3220
sf::Color Screen::containerGray = sf::Color(20, 20, 20);	// #141414

/* Constructor */

Screen::Screen() {
	// Reserve space for vectors to avoid resizing and copying during runtime
	buttons.reserve(5);
	texts.reserve(5);
	sprites.reserve(5);
	containers.reserve(5);
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


/* Public functions */

void Screen::setActive(bool state) { active = state; }
bool Screen::getActive() const { return active; }

void Screen::update(sf::Event& e, sf::RenderWindow& window) {
	if (!active)
		return;

	for (Button& b : buttons)
		b.update(e, window);

	for (Container& c : containers)
		c.update(e, window);
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!active)
		return;

	for (const Container& c : containers)
		c.draw(target, states);
	
	for (const sf::Sprite& sp : sprites)
		target.draw(sp, states);

	for (const Button& b : buttons)
		b.draw(target, states);

	for (const sf::Text& t : texts)
		target.draw(t, states);
}