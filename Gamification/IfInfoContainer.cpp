#include "IfInfoContainer.h"
#include "Screen.h"

IfInfoContainer::IfInfoContainer() {}

IfInfoContainer::IfInfoContainer(Screen* parent, sf::Font& font) : Container(parent) {
	LEVEL_TEXT = "Level: ";
	SCORE_TEXT = "Score: ";
	HIGH_SCORE_TEXT = "High Score: ";
	LIVES_TEXT = "Lives: ";

	background = sf::RectangleShape(sf::Vector2f(615, 35));
	background.setPosition(20, 665);
	background.setFillColor(Screen::containerGray);
	background.setOutlineColor(Screen::blue);
	background.setOutlineThickness(3);

	int fontSize = 15;
	int textY = 672;
	addText(LEVEL_TEXT, font, fontSize);
	texts.at(0).setPosition(25, textY);
	addText(SCORE_TEXT, font, fontSize);
	texts.at(1).setPosition(225, textY);
	addText(HIGH_SCORE_TEXT, font, fontSize);
	texts.at(2).setPosition(325, textY);
	addText(LIVES_TEXT, font, fontSize);
	texts.at(3).setPosition(550, textY);
}

void IfInfoContainer::updateLevel(const int level) {
	texts.at(0).setString(LEVEL_TEXT + std::to_string(level));
}

void IfInfoContainer::updateScore(const int score) {
	texts.at(1).setString(SCORE_TEXT + std::to_string(score));
}

void IfInfoContainer::updateHighScore(const int highScore) {
	texts.at(2).setString(HIGH_SCORE_TEXT + std::to_string(highScore));
}

void IfInfoContainer::updateLives(const int lives) {
	texts.at(3).setString(LIVES_TEXT + std::to_string(lives));
}

void IfInfoContainer::reset() {
	texts.at(0).setString(LEVEL_TEXT);
	texts.at(1).setString(SCORE_TEXT);
	texts.at(2).setString(HIGH_SCORE_TEXT);
	texts.at(3).setString(LIVES_TEXT);
}