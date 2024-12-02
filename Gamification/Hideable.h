#ifndef HIDEABLE_H
#define HIDEABLE_H

#include <SFML/Graphics.hpp>

class Hideable : public sf::Drawable
{
	protected:
		bool toDraw;
	public:
		void show() { toDraw = true; }
		void hide() { toDraw = false; }
		bool getToDraw() { return toDraw; }
};

#endif