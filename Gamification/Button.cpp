#include "Button.h"
#include <iostream>

/* Constructors */

/// <summary>
/// Empty default constructor. Do not use.
/// </summary>
Button::Button() { }

/// <summary>
/// Creates a button with a background and text
/// </summary>
/// <param name="screen">The parent screen of this button</param>
/// <param name="id">The id of this button within the parent screen</param>
/// <param name="str">The text to display on this button</param>
/// <param name="font">The font to use for this button's text</param>
/// <param name="position">The position of the top-left corner of this button</param>
/// <param name="size">The size of this button</param>
/// <param name="fontSize">The character size of this button's text</param>
Button::Button(Screen* screen, int id, std::string str, sf::Font& font, sf::Vector2f position, sf::Vector2f size, unsigned int fontSize) {
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


/* Getters */

/// <summary>
/// Returns the text displayed on the button
/// </summary>
std::string Button::getText() const { return text.getString(); }

/// <summary>
/// Returns the current state of the button
/// </summary>
ButtonState Button::getState() const { return state; }


/* Setters */

/// <summary>
/// Sets this button's text
/// </summary>
/// <param name="txt">The new text to display</param>
void Button::setText(std::string txt) { text.setString(txt); }

/// <summary>
/// Sets the offset of the text in relation to the top-left corner of the button's boundary
/// </summary>
/// <param name="newOffset">The new text offset to be applied</param>
void Button::setTextOffset(sf::Vector2f newOffset) {
	textOffset = newOffset;
	text.setPosition(boundary.getPosition() + textOffset);
}


/* Protected functions */

/// <summary>
/// Function to be called when the button's state has changed to Normal.
/// Changes the background color to the normal color.
/// </summary>
void Button::onNormal() {
	background.setFillColor(normalColor);
}

/// <summary>
/// Function to be called when the button's state has changed to Hovered.
/// Changes the background color to the hovered color.
/// </summary>
void Button::onHover() {
	background.setFillColor(hoveredColor);
}

/// <summary>
/// Function to be called when the button's state has changed to Clicked.
/// Changes the background color to the clicked color.
/// Invokes the parent screen's clickButton function using this button's ID.
/// </summary>
void Button::onClick() {
	background.setFillColor(clickedColor);
	(*parent).clickButton(clickID);
}


/* Overriden functions */

/// <summary>
/// Draws the components that make up this button
/// </summary>
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(background, states);
	target.draw(text, states);
}

/// <summary>
/// Sets the new position of the button's top-left corner relative to the window's top-left corner 
/// </summary>
void Button::setPosition(float x, float y) {
	boundary.left = x;
	boundary.top = y;
	background.setPosition(x, y);
	text.setPosition(x + textOffset.x, y + textOffset.y);
}


/* Other functions */

/// <summary>
/// Checks to see if the button's state has changed and updates it if so.
/// Calls the corresponding state change function if the state has changed.
/// </summary>
/// <param name="e">The event that has occured</param>
/// <param name="window">The window that this button is a part of</param>
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