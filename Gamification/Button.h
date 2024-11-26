#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Screen.h"

class Screen;

enum ButtonState {
	Normal,
	Hovered,
	Clicked
};

class Button : public sf::Drawable {
	private:
		ButtonState state;

		sf::Color normalColor;
		sf::Color hoveredColor;
		sf::Color clickedColor;

		sf::Rect<float> boundary;
		sf::RectangleShape background;
		sf::Text text;
		sf::Vector2f textOffset;

		int clickID;
		Screen* parent;
	protected:
		/// <summary>
		/// Function to be called when the button's state has changed to Normal.
		/// Changes the background color to the normal color.
		/// </summary>
		virtual void onNormal();

		/// <summary>
		/// Function to be called when the button's state has changed to Hovered.
		/// Changes the background color to the hovered color.
		/// </summary>
		virtual void onHover();

		/// <summary>
		/// Function to be called when the button's state has changed to Clicked.
		/// Changes the background color to the clicked color.
		/// Invokes the parent screen's clickButton function using this button's ID.
		/// </summary>
		virtual void onClick();
	public:
		/// <summary>
		/// Empty default constructor. Do not use.
		/// </summary>
		Button();

		/// <summary>
		/// Creates a button with a background and text.
		/// </summary>
		/// <param name="screen">The parent screen of this button.</param>
		/// <param name="id">The id of this button within the parent screen.</param>
		/// <param name="str">The text to display on this button.</param>
		/// <param name="font">The font to use for this button's text.</param>
		/// <param name="position">The position of the top-left corner of this button.</param>
		/// <param name="size">The size of this button.</param>
		/// <param name="fontSize">The character size of this button's text.</param>
		Button(Screen* parent, int id, std::string str, sf::Vector2f position,
			sf::Vector2f size, sf::Font& font, unsigned int fontSize = 15);

		// Destructor
		~Button();

		/// <summary>
		/// Sets this button's text.
		/// </summary>
		/// <param name="txt">The new text to display.</param>
		void setText(std::string txt);

		/// <summary>
		/// Sets the offset of the text in relation to the top-left corner of the button's boundary.
		/// </summary>
		/// <param name="newOffset">The new text offset to be applied.</param>
		void setTextOffset(sf::Vector2f newOffset);

		/// <summary>
		/// Draws the components that make up this button.
		/// </summary>
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		/// <summary>
		/// Sets the new position of the button's top-left corner relative to the window's top-left corner.
		/// </summary>
		virtual void setPosition(float x, float y);

		/// <summary>
		/// Checks to see if the button's state has changed and updates it if so.
		/// Calls the corresponding state change function if the state has changed.
		/// </summary>
		/// <param name="e">The event that has occured.</param>
		/// <param name="window">The window that this button is a part of.</param>
		virtual void update(sf::Event& e, sf::RenderWindow& window);
};

#endif