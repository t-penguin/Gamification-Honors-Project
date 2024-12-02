#include "IfGame.h"
#include <iostream>

/* Constructors */

IfGame::IfGame() { }
IfGame::IfGame(sf::RenderWindow& window, sf::Font& font) {
	gameInProgress = false;
	maxLevels = 20;
	roundDelay = 0.3f;
	delayRemaining = roundDelay;

	// Reserve space for vectors to avoid resizing and copying during runtime
	buttons.reserve(15);
	texts.reserve(20);
	sprites.reserve(5);
	containers.reserve(5);

	sf::Vector2u screenSize = window.getSize();
	sf::Vector2u screenMiddle(screenSize.x / 2, screenSize.y / 2);
	int headerFontSize = 30;
	int regularFontSize = 15;

	// Default values for things to be set later
	lowerBound = -1000;
	threshold = -1000;
	correctThresholdIndex = -1;
	correctOperatorIndex = -1;
	boolOp = None;
	
	// Header text
	addText("Match The Range", font, headerFontSize);
	texts.at(0).setPosition((int)(screenMiddle.x - texts.at(0).getGlobalBounds().width / 2), 15);

	// Start button
	sf::Vector2f buttonSize(100, 35);
	sf::Vector2f buttonPos((int)(screenMiddle.x - buttonSize.x / 2), (int)(screenSize.y - buttonSize.y - 20));
	addButton("Start Game", buttonPos, buttonSize, font);

	// Submit Button
	buttonSize = sf::Vector2f(75, 35);
	buttonPos = sf::Vector2f(1040, 533);
	addButton("Submit", buttonPos, buttonSize, font);
	buttons.at(1).hide();

	// Play area background
	addContainer(this);
	containers.at(0).setSize(615, 575);
	containers.at(0).setOutlineThickness(3);
	containers.at(0).setOutlineColor(yellow);
	containers.at(0).setFillColor(containerGray);
	containers.at(0).setPosition(sf::Vector2f(20, 70));
	containers.at(0).show();

	// Number line image
	numLineTexture = sf::Texture();
	if (!numLineTexture.loadFromFile("NumberLine.png")) {
		std::cout << "Could not load number line texture\n";
		return;
	}
	addSprite(numLineTexture);
	sprites.at(0).setPosition(32, 600);

	// Number line text
	for (int i = 1; i < 16; i++) {
		addText("", font, regularFontSize);
		setNumberLineTextPosition(texts.at(i), i - 1);
	}

	answerLine = AnswerLine();

	// Answer choice buttons container
	sf::Vector2f buttonContainerPos(screenSize.x * 3 / 4 - 185, screenSize.y / 2);
	addContainer(this);
	containers.at(1).setSize(370, 100);
	containers.at(1).setOutlineThickness(3);
	containers.at(1).setOutlineColor(blue);
	containers.at(1).setFillColor(containerGray);
	containers.at(1).setPosition(buttonContainerPos);

	// Answer choice buttons
	int buttonID = 2;
	
	thresholdOptionIndexes.reserve(6);
	operatorOptionIndexes.reserve(6);
	containers.at(1).reserveSizeForButtons(12);
	for (int i = 0; i < 6; i++) {
		int posX = (buttonContainerPos.x + 10) + ((60) * i);
		int posY = buttonContainerPos.y + 10;
		
		// Treshold buttons
		addBlankOptionButton(buttonID, posX, posY, font);
		thresholdOptionIndexes.push_back(buttonID - 2);

		buttonID++;
		posY += 45;

		// Bool operator buttons
		addBlankOptionButton(buttonID, posX, posY, font);
		operatorOptionIndexes.push_back(buttonID - 2);
		buttonID++;
	}

	// Answer Text
	answerText = IfAnswerText(font);
	answerText.hide();

	info = IfInfoContainer(this, font);
	info.hide();
}


/* Destructor */

IfGame::~IfGame() { }


/* Screen overrides */

void IfGame::clickButton(int id) {
	// Start Game button
	if (id == 0) {
		startGame();
		return;
	}

	// TODO: Button to return to the main screen 

	if (!gameInProgress)
		return;

	// Submit answer button
	if (id == 1) {
		submitAnswer();
		return;
	}

	// Threshold buttons
	if (id >= 2 && id <= 13) {
		std::string txt = containers.at(1).getButtonAt(id - 2).getText();

		if (id % 2 == 0) {
			answerText.setThreshold(txt);
			playerThresholdID = id;
		}
		else {
			answerText.setBoolOperator(txt);
			playerOperatorID = id;
		}
		return;
	}

	// Button with no function
	std::cout << "Clicked button with ID " << id << std::endl;
}

void IfGame::update(const float dt, sf::RenderWindow& window) {
	if (!gameInProgress)
		return;

	if (delayRemaining > 0) {
		delayRemaining -= dt;
		if (delayRemaining <= 0)
			startRound();
		return;
	}

	if (!answerLine.getToDraw())
		return;

	if (answerLine.isAtBottom()) {
		std::cout << "Answer Line has reached the bottom\n";
		submitAnswer();
	}
	else {
		answerLine.dropDown(dt);
	}
}

void IfGame::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	answerText.draw(target, states);
	Screen::draw(target, states);
	answerLine.draw(target, states);
	info.draw(target, states);
}


/* Helper functions */

void IfGame::addBlankOptionButton(int buttonID, int posX, int posY, sf::Font& font) {
	Button* curButton = nullptr;
	sf::Vector2f size(50, 35);
	sf::Vector2f offset(17, 7);

	containers.at(1).addButton("", buttonID, sf::Vector2f(posX, posY), size, font);
	curButton = &containers.at(1).getButtonAt(buttonID - 2);
	curButton->show();
	curButton->setTextOffset(offset);
}

void IfGame::generateChoices() {
	std::vector<int> curThresholds;
	std::vector<BoolOperator> curOperators;
	std::string buttonText;

	for (int i = 0; i < 6; i++) {
		// Generate threshold buttons text
		if (i == correctThresholdIndex) { // Use the correct threshold answer for this index
			buttonText = std::to_string(threshold);
			curThresholds.push_back(threshold);
		}
		else { // Generate a unique dummy threshold for this index
			int dummyThreshold = lowerBound + std::rand() % 14 + 1;
			bool thresholdExists = std::count(curThresholds.begin(), curThresholds.end(), dummyThreshold) != 0;
			while (dummyThreshold == threshold || thresholdExists)
			{
				dummyThreshold = lowerBound + std::rand() % 14 + 1;
				thresholdExists = std::count(curThresholds.begin(), curThresholds.end(), dummyThreshold) != 0;
			}

			buttonText = std::to_string(dummyThreshold);
			curThresholds.push_back(dummyThreshold);
		}
		// Set the button text for the corresponding threshold button
		int index = thresholdOptionIndexes.at(i);
		containers.at(1).getButtonAt(index).setText(buttonText);

		// Generate bool operator buttons text
		if (i == correctOperatorIndex) { // Use the correct operator answer for this index
			buttonText = BoolOperatorToString(boolOp);
			curOperators.push_back(boolOp);
		}
		else { // Generate a unique dummy operator for this index
			BoolOperator dummyOperator = (BoolOperator)(std::rand() % 6 + 1);
			bool operatorExists = std::count(curOperators.begin(), curOperators.end(), dummyOperator) != 0;
			while (dummyOperator == boolOp || operatorExists)
			{
				dummyOperator = (BoolOperator)(std::rand() % 6 + 1);
				operatorExists = std::count(curOperators.begin(), curOperators.end(), dummyOperator) != 0;
			}

			buttonText = BoolOperatorToString(dummyOperator);
			curOperators.push_back(dummyOperator);
		}
		// Set the button text for the corresponding operator button
		index = operatorOptionIndexes.at(i);
		containers.at(1).getButtonAt(index).setText(buttonText);
	}
}

void IfGame::populateNumberLine() {
	if (lowerBound < -99 || lowerBound > 84) {
		std::cout << "Bounds not set properly, can't populate number line.\n";
		return;
	}

	for (int i = 1; i < 16; i++) {
		texts.at(i).setString(std::to_string(lowerBound + i - 1));
		setNumberLineTextPosition(texts.at(i), i - 1);
	}
}

void IfGame::createAnswerLine() {
	answerLine.setThresholdPosition(lowerBound, threshold);
	answerLine.setBooleanOperator(boolOp);
	answerLine.show();
}

void IfGame::submitAnswer() {
	answerLine.reset();
	if (playerThresholdID == thresholdOptionIndexes.at(correctThresholdIndex) + 2
		&& playerOperatorID == operatorOptionIndexes.at(correctOperatorIndex) + 2) {
		std::cout << "Correct!\n";
		onCorrect();
		score++;
		info.updateScore(score);
	}
	else {
		std::cout << "Wrong!\n";
		onWrong();
		lives--;
		info.updateLives(lives);
	}

	if (lives <= 0) {
		endGame(false);
		return;
	}

	currentLevel++;
	if (currentLevel > maxLevels) {
		endGame(true);
		return;
	}

	info.updateLevel(currentLevel);
	std::cout << "Moving on to level " << currentLevel << std::endl;
	answerLine.increaseSpeed();
	delayRemaining = roundDelay;
}

void IfGame::setNumberLineTextPosition(sf::Text& text, int index) {
	int numLineCenter = 32 + (42 * index);
	int textCenterX = (text.getGlobalBounds().width / 2);
	text.setPosition(numLineCenter - textCenterX, 620);
}

std::string IfGame::BoolOperatorToString(BoolOperator op) const {
	switch (op) {
		case LessThan:
			return "<";
		case LessThanOrEqualTo:
			return "<=";
		case GreaterThan:
			return ">";
		case GreaterThanOrEqualTo:
			return ">=";
		case NotEqualTo:
			return "!=";
		case EqualTo:
			return "==";
		default:
			return "None";
	}
}

void IfGame::startGame() {
	std::cout << "Starting game!\n";

	// Hide the start button
	buttons.at(0).hide();

	// Show all the answer choice buttons
	containers.at(1).show();
	buttons.at(1).show();

	currentLevel = 1;
	info.updateLevel(currentLevel);
	score = 0;
	info.updateScore(score);
	lives = 3;
	info.updateLives(lives);
	info.setOutlineColor(Screen::blue);
	info.show();
	startRound();
}

void IfGame::endGame(bool finished) {
	if (finished) {
		std::cout << "You won with a score of " << score << "!\n";
	}
	else {
		std::cout << "You lost... You made it to level " << currentLevel;
		std::cout << " with a score of " << score << "...\n";
	}
}

void IfGame::startRound() {
	reset();
	gameInProgress = true;
	playerThresholdID = 0;
	playerOperatorID = 0;

	std::srand(std::time(0));
	lowerBound = std::rand() % 184 - 99;
	threshold = lowerBound + std::rand() % 13 + 1;
	boolOp = (BoolOperator)(std::rand() % 6 + 1);

	correctThresholdIndex = std::rand() % 6;
	correctOperatorIndex = std::rand() % 6;
	std::string buttonText;
	generateChoices();
	populateNumberLine();
	createAnswerLine();
}

void IfGame::changeOutlineColors(sf::Color& color) {
	answerText.setOutlineColor(color);
	info.setOutlineColor(color);
	containers.at(0).setOutlineColor(color);	// Play Area
	containers.at(1).setOutlineColor(color);	// Buttons Container
}

void IfGame::onCorrect() { changeOutlineColors(Screen::green); }

void IfGame::onWrong() { changeOutlineColors(Screen::red); }

void IfGame::reset() {
	answerLine.reset();
	answerText.reset();
	answerText.show();
	info.setOutlineColor(Screen::blue);
	containers.at(0).setOutlineColor(Screen::yellow);	// Play Area
	containers.at(1).setOutlineColor(Screen::blue);		// Buttons Container
}