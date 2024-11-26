#ifndef IFGAME_H
#define IFGAME_H

#include <cstdlib>
#include <ctime>
#include "Screen.h"

enum BoolOperator {
	None,
	LessThan,
	LessThanOrEqualTo,
	GreaterThan,
	GreaterThanOrEqualTo,
	NotEqualTo,
	EqualTo
};

class IfGame : public Screen {
	private:
		bool gameInProgress;
		int lowerBound;
		int upperBound;
		int threshold;
		BoolOperator boolOp;
		int correctThresholdIndex;
		int correctOperatorIndex;

		std::vector<int> thresholds;
		std::vector<int> operators;

		sf::Texture numLineTexture;

		void generateChoices();
		void populateNumberLine();
		void createAnswerLine();
		void setNumberLineTextPosition(sf::Text&, int);
		std::string BoolOperatorToString(BoolOperator) const;
	public:
		IfGame();
		IfGame(sf::RenderWindow&, sf::Font&);

		~IfGame();

		virtual void clickButton(int) override;

		void startGame();
		void startRound();
};

#endif