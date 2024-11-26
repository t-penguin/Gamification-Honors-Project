#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include "Button.h"

class Button;
class Screen : public sf::Drawable {
	protected:
		std::vector<Button> buttons;
		std::vector<sf::Text> texts;
		std::vector<sf::Sprite> sprites;
		std::vector<sf::Shape*> shapes;

		sf::Color yellow;
		sf::Color green;
		sf::Color red;
	public:
		Screen();
		~Screen();

		Button* getButtonAt(int) const;
		sf::Text* getTextAt(int) const;
		sf::Shape* getShapeAt(int) const;

		void addButton(Button);
		void removeButtonAt(int);
		void addText(sf::Text);
		void removeTextAt(int);
		void addSprite(sf::Sprite);
		void addShape(sf::Shape*);
		void removeShapeAt(int);

		virtual void clickButton(int) = 0;
		virtual void update(sf::Event&, sf::RenderWindow&);
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif