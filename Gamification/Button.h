#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
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
		// Helper functions
		virtual void onNormal();
		virtual void onHover();
		virtual void onClick();
	public:
		// Constructors
		Button();
		Button(Screen*, int, std::string, sf::Font&, sf::Vector2f, sf::Vector2f, unsigned int = 15);

		// Destructor
		~Button();

		// Getters
		std::string getText() const;
		ButtonState getState() const;

		// Setters
		void setText(std::string);
		void setTextOffset(sf::Vector2f);

		// Overriden functions
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		virtual void setPosition(float, float);

		// Other functions
		virtual void update(sf::Event&, sf::RenderWindow&);
};

#endif