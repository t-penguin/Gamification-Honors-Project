#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "Screen.h"

class MainScreen : public Screen {
	private:
		int gameIndex;
		Container* descriptionText;
		Container* ifGameSummary;
		Container* switchGameSummary;
	public:
		MainScreen();
		MainScreen(sf::RenderWindow& window, sf::Font& font);
		~MainScreen();

		int getGameIndex() const;
		void resetGameIndex();
		void clickButton(int buttonID) override;
};

#endif