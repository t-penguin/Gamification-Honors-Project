#include "Container.h"

Container::Container() { }

Container::Container(Screen* parent, const sf::Vector2f& size, const sf::Vector2f& pos) {
	this->parent = parent;
	texts.reserve(5);
	background.setSize(size);
	background.setPosition(pos);
	background.setOutlineColor(Screen::blue);
	background.setOutlineThickness(3);
	background.setFillColor(Screen::containerGray);
}

void Container::reserveSizeForButtons(int numButtons) { buttons.reserve(numButtons); }

void Container::setPosition(sf::Vector2f pos) { background.setPosition(pos); }
void Container::setSize(int x, int y) { background.setSize(sf::Vector2f(x, y)); }
void Container::setFillColor(sf::Color& color) { background.setFillColor(color); }
void Container::setOutlineThickness(int thickness) { background.setOutlineThickness(thickness); }
void Container::setOutlineColor(sf::Color& color) { background.setOutlineColor(color); }

void Container::addText(std::string txt, sf::Font& font, int fontSize) {
	texts.emplace_back(txt, font, fontSize);
}

void Container::addButton(std::string txt, int id, sf::Vector2f pos, sf::Vector2f size, sf::Font& font) {
	buttons.emplace_back(parent, id, txt, pos, size, font);
}

sf::Vector2f Container::getSize() const { return background.getSize(); }
sf::Vector2f Container::getPosition() const { return background.getPosition(); }
Button& Container::getButtonAt(int index) { return buttons.at(index); }
sf::Text& Container::getTextAt(int index) { return texts.at(index); }

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!toDraw)
		return;
	
	target.draw(background, states);
	
	for (const Button& b : buttons)
		b.draw(target, states);

	for (const sf::Text& t : texts)
		target.draw(t, states);
}

void Container::update(sf::Event& e, sf::RenderWindow& window) {
	for (Button& b : buttons)
		b.update(e, window);
}