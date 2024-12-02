#ifndef IFGAME_H
#define IFGAME_H

#include <cstdlib>
#include <ctime>
#include "Screen.h"
#include "BoolOperatorNames.h"
#include "AnswerLine.h"
#include "IfAnswerText.h"
#include "IfInfoContainer.h"

class IfGame : public Screen {
	private:
		bool gameInProgress;
		int lowerBound;
		int threshold;
		BoolOperator boolOp;
		
		std::vector<int> thresholdOptionIndexes;
		int correctThresholdIndex;
		int playerThresholdID;

		std::vector<int> operatorOptionIndexes;
		int correctOperatorIndex;
		int playerOperatorID;

		sf::Texture numLineTexture;
		AnswerLine answerLine;
		IfAnswerText answerText;
		IfInfoContainer info;

		float roundDelay;
		float delayRemaining;
		int currentLevel;
		int maxLevels;
		int score;
		int lives;

		void addBlankOptionButton(int buttonID, int posX, int posY, sf::Font& font);

		/// <summary>
		/// Generates random wrong answer choices for the thresholds and operators within their respective 
		/// ranges and sets the corresponding button's text. Two choices will not be random as they are correct.
		/// </summary>
		void generateChoices();

		/// <summary>
		/// Populates the text below the number line texture given that the lower bound is set appropriately.
		/// </summary>
		void populateNumberLine();

		/// <summary>
		/// Creates the answer line using the lower bound, threshold, and boolean operator.
		/// </summary>
		void createAnswerLine();

		void submitAnswer();

		/// <summary>
		/// Adjusts each text object underneath the number line so they appear centered.
		/// </summary>
		/// <param name="text">: The text object to adjust.</param>
		/// <param name="index">: The index of the text object along the number line.</param>
		void setNumberLineTextPosition(sf::Text& text, int index);

		/// <summary>
		/// Returns a string representing the given BoolOperator type.
		/// </summary>
		std::string BoolOperatorToString(BoolOperator op) const;

		/// <summary>
		/// Starts the game.
		/// </summary>
		void startGame();

		void endGame(bool finished);

		/// <summary>
		/// Starts a round in the game.
		/// </summary>
		void startRound();

		void changeOutlineColors(sf::Color& color);

		void onCorrect();

		void onWrong();

		void reset();
	public:
		/// <summary>
		/// Empty default constructor. Do not use.
		/// </summary>
		IfGame();

		/// <summary>
		/// Creates the If Game screen and all of its components.
		/// </summary>
		/// <param name="window">: The window this screen is a part of.</param>
		/// <param name="font">: The font to use for all texts.</param>
		IfGame(sf::RenderWindow& window, sf::Font& font);

		~IfGame();

		/// <summary>
		/// Defines what to do for specific button IDs. Should be called by a button using its parent member.
		/// </summary>
		/// <param name="id">: The ID of the button that was clicked.</param>
		virtual void clickButton(int id) override;

		virtual void update(const float dt, sf::RenderWindow& window) override;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif