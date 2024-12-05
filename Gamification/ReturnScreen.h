#ifndef RETURNSCREEN_H
#define RETURNSCREEN_H

#include "Screen.h"

class ReturnScreen : public Screen {
	private:
		bool returnToMain;
	public:
		ReturnScreen();
		ReturnScreen(sf::Window& window, sf::Font& font);

		bool getReturn() const;
		void resetReturn();

		void clickButton(int buttonID) override;
};

#endif