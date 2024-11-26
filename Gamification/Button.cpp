#include "Button.h"
#include <iostream>

/* Constructors */

Button::Button() { }

Button::Button(Screen* screen, int id, std::string str, sf::Vector2f position, sf::Vector2f size, sf::Font& font, unsigned int fontSize) {
	state = Normal;
	normalColor = sf::Color(79, 79, 79);
	hoveredColor = sf::Color(68, 68, 68);
	clickedColor = sf::Color(55, 55, 55);

	parent = screen;
	clickID = id;
	boundary = sf::Rect<float>(position, size);

	text = sf::Text(str, font, fontSize);
	float textWidth = text.getGlobalBounds().width;
	float textHeight = text.getGlobalBounds().height;
	textOffset = sf::Vector2f(sf::Vector2f(std::floor((size.x - textWidth) / 2), std::floor((size.y - textHeight) / 2 - 5)));
	text.setPosition(position + textOffset);

	background = sf::RectangleShape(size);
	background.setPosition(position);
	background.setFillColor(normalColor);
}


/* Destructor */

Button::~Button() { }


/* Setters */

void Button::setText(std::string txt) { text.setString(txt); }

void Button::setTextOffset(sf::Vector2f newOffset) {
	textOffset = newOffset;
	text.setPosition(boundary.getPosition() + textOffset);
}


/* Protected functions */

void Button::onNormal() {
	background.setFillColor(normalColor);
}

void Button::onHover() {
	background.setFillColor(hoveredColor);
}

void Button::onClick() {
	background.setFillColor(clickedColor);
	(*parent).clickButton(clickID);
}


/* Overriden functions */

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(background, states);
	target.draw(text, states);
}

void Button::setPosition(float x, float y) {
	boundary.left = x;
	boundary.top = y;
	background.setPosition(x, y);
	text.setPosition(x + textOffset.x, y + textOffset.y);
}


/* Other functions */

void Button::update(sf::Event& e, sf::RenderWindow& window) {
	ButtonState newState = state;

	// Sets the button to its normal state when the cursor is not within its boundary
	sf::Vector2i cursorPosition = sf::Mouse::getPosition(window);
	if (!boundary.contains(cursorPosition.x, cursorPosition.y))
		newState = Normal;

	/* If this section executes, the cursor is within the boundary of the button
	 * Sets the button to its clicked state when a left click event has been sent */
	else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
		newState = Clicked;

	/* If this section executes, the cursor is hovering the button (not clicking)
	 * Sets the button to its hovered state when the cursor is only hovering over the button */
	else if (e.type == sf::Event::MouseMoved || (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left))
		newState = Hovered;
	
	// The state has not changed, do nothing and exit
	if (newState == state)
		return;

	this->state = newState;
	switch (state) {
		case Normal:
			onNormal();
			break;
		case Hovered:
			onHover();
			break;
		case Clicked:
			onClick();
			break;
	}
}