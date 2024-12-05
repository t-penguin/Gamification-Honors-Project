#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include "Button.h"
#include "Container.h"

class Button;
class Container;
class Screen : public sf::Drawable {
	protected:
		std::vector<Button> buttons;
		std::vector<sf::Text> texts;
		std::vector<sf::Sprite> sprites;
		std::vector<Container> containers;

		/// <summary>
		/// Creates and adds a button to the end of the buttons list. Implicitly passes the calling screen
		/// as the parent and the current list size as the ID of the button (thus making its ID its index
		/// in the list.
		/// </summary>
		/// <param name="str">: The text to be displayed on the button.</param>
		/// <param name="position">: The position of the top left corner of the button.</param>
		/// <param name="size">: The size (width and height) of the button.</param>
		/// <param name="font">: The font to use for the text.</param>
		/// <param name="fontSize">: The size of the font to be used.</param>
		void addButton(std::string str, sf::Vector2f position, sf::Vector2f size, sf::Font& font, unsigned int fontSize = 15);
		
		/// <summary>
		/// Creates and adds a text object to the end of the texts list.
		/// </summary>
		/// <param name="str">: The string to be displayed.</param>
		/// <param name="font">: The font to be used. </param>
		/// <param name="fontSize">: The size of the characters. </param>
		void addText(std::string str, sf::Font& font, unsigned int fontSize = 15);

		/// <summary>
		/// Creates and adds an empty Sprite object to the end of the sprites list.
		/// </summary>
		void addSprite();

		/// <summary>
		/// Creates and adds a Sprite object to the end of the sprites list using the supplied texture.
		/// </summary>
		void addSprite(sf::Texture& texture);

		/// <summary>
		/// Creates and adds a Container object to the end of the containers list. The calling Screen is passed as the parent.
		/// </summary>
		void addContainer(const sf::Vector2f& size, const sf::Vector2f& pos);
	public:
		static sf::Color blue;
		static sf::Color yellow;
		static sf::Color green;
		static sf::Color red;
		static sf::Color containerGray;

		/// <summary>
		/// Releases memory held by the shapes vector.
		/// </summary>
		~Screen();

		/// <summary>
		/// Executes an action based on the ID of the button that is clicked. Pure virtual function
		/// that should be implemented by all derived classes that wish to be instantiated.
		/// </summary>
		virtual void clickButton(int id) = 0;

		/// <summary>
		/// Sends event updates to screen elements. Can be overriden.
		/// </summary>
		/// <param name="e">: The event that has occured.</param>
		/// <param name="window">: The window this screen is a part of.</param>
		virtual void update(sf::Event& e, sf::RenderWindow& window);

		/// <summary>
		/// Used to update screen elements that are dependent on the time elapsed.
		/// Should be called every frame to be accurate.
		/// </summary>
		/// <param name="dt">: The time elapsed since the previous frame.</param>
		/// <param name="window">: The window this screen is a part of.</param>
		virtual void update(const float dt, sf::RenderWindow& window) = 0;

		/// <summary>
		/// Draws all the elements on the screen. Can be overriden to change the order 
		/// in which elements are drawn. 
		/// </summary>
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif