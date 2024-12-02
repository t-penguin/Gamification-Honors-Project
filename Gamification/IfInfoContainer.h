#ifndef IFINFOCONTAINER_H
#define IFINFOCONTAINER_H

#include "Container.h"

class IfInfoContainer : public Container {
	private:
		std::string LEVEL_TEXT;
		std::string SCORE_TEXT;
		std::string HIGH_SCORE_TEXT;
		std::string LIVES_TEXT;

		sf::Text levelText;
		sf::Text scoreText;
		sf::Text highScoreText;
		sf::Text livesText;
	public:
		IfInfoContainer();
		IfInfoContainer(Screen* parent, sf::Font& font);
		void updateLevel(const int level);
		void updateScore(const int score);
		void updateHighScore(const int highScore);
		void updateLives(const int lives);
		void reset();
};

#endif