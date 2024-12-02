#ifndef CONTAINER_H
#define CONTAINER_H

#include "Hideable.h"
#include "Screen.h"

class Screen;
class Button;
class Container : public Hideable {
	protected:
		Screen* parent;

		sf::RectangleShape background;
		std::vector<Button> buttons;
		std::vector<sf::Text> texts;
	public:
		Container();
		Container(Screen* parent);
		void reserveSizeForButtons(int numButtons);
		void setPosition(sf::Vector2f pos);
		void setSize(int x, int y);
		void setFillColor(sf::Color& color);
		void setOutlineThickness(int thickness);
		void setOutlineColor(sf::Color& color);
		void addText(std::string txt, sf::Font& font, int fontSize = 15);
		void addButton(std::string txt, int id, sf::Vector2f pos, sf::Vector2f size, sf::Font& font);

		Button& getButtonAt(int index);
		sf::Text& getTextAt(int index);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates) const override;
		virtual void update(sf::Event& e, sf::RenderWindow& window);
};

#endif