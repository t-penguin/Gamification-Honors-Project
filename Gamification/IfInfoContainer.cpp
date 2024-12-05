#include "IfInfoContainer.h"
#include "Screen.h"

IfInfoContainer::IfInfoContainer() {}

IfInfoContainer::IfInfoContainer(Screen* parent, sf::Font& font) : Container(parent, sf::Vector2f(615, 35), sf::Vector2f(20, 665)) {
	LEVEL_TEXT = "Level: ";
	SCORE_TEXT = "Score: ";
	HIGH_SCORE_TEXT = "High Score: ";
	LIVES_TEXT = "Lives: ";

	int fontSize = 20;
	int textY = 669;
	addText(LEVEL_TEXT, font, fontSize);
	texts.at(0).setPosition(25, textY);
	addText(SCORE_TEXT, font, fontSize);
	texts.at(1).setPosition(215, textY);
	addText(HIGH_SCORE_TEXT, font, fontSize);
	texts.at(2).setPosition(355, textY);
	addText(LIVES_TEXT, font, fontSize);
	texts.at(3).setPosition(550, textY);
	texts.at(3).setFillColor(Screen::falseColor);
}

void IfInfoContainer::updateLevel(const int level) {
	texts.at(0).setString(LEVEL_TEXT + std::to_string(level) +  " / 20");
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