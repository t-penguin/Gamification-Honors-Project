#include "IfGame.h"
#include "Logger.h"

/* Constructors */

IfGame::IfGame() { }
IfGame::IfGame(sf::RenderWindow& window, sf::Font& font) {
	gameInProgress = false;
	maxLevels = 20;
	roundDelay = 0.3f;
	delayRemaining = roundDelay;
	sf::Vector2u screenSize = window.getSize();
	sf::Vector2u screenMiddle(screenSize.x / 2, screenSize.y / 2);
	sf::Vector2f size;
	sf::Vector2f pos;

	// Default values for things to be set later
	lowerBound = -1000;
	threshold = -1000;
	correctThresholdIndex = -1;
	correctOperatorIndex = -1;
	boolOp = None;

	// Initialize Container pointers
	playArea = nullptr;
	howTo = nullptr;
	choiceButtons = nullptr;

	pos.x = screenSize.x * 3 / 4 - 185;
	pos.y = screenSize.y / 2 + 70;
	addContainer(sf::Vector2f(615, 575), sf::Vector2f(20, 70));
	addContainer(sf::Vector2f(615, 345), sf::Vector2f(screenMiddle.x + 10, 70));
	addContainer(sf::Vector2f(370, 100), pos);
	playArea = &containers.at(0);
	playArea->show();
	howTo = &containers.at(1);
	howTo->show();
	choiceButtons = &containers.at(2);
	choiceButtons->hide();

	int headerFontSize = 30;
	int regularFontSize = 15;
	
	// Header text
	addText("Match The Range", font, headerFontSize);
	texts.at(0).setPosition((int)(screenMiddle.x - texts.at(0).getGlobalBounds().width / 2), 15);

	// Start button
	size.x = 100;
	size.y = 35;
	pos.x = (int)(screenMiddle.x - size.x / 2);
	pos.y = (int)(screenSize.y - size.y - 20);
	addButton("Start Game", pos, size, font);

	// Submit Button
	size.x = 75;
	pos.x = 1040;
	pos.y = 578;
	addButton("Submit", pos, size, font);
	buttons.at(1).hide();

	// Number line image
	numLineTexture = sf::Texture();
	if (!numLineTexture.loadFromFile("NumberLine.png")) {
		Logger::log("Could not load number line texture\n");
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

	// Answer choice buttons
	int buttonID = 2;
	thresholdOptionIndexes.reserve(6);
	operatorOptionIndexes.reserve(6);
	choiceButtons->reserveSizeForButtons(12);
	pos = choiceButtons->getPosition();
	for (int i = 0; i < 6; i++) {
		int posX = (pos.x + 10) + ((60) * i);
		int posY = pos.y + 10;
		
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

	// Game Data Info Container
	info = IfInfoContainer(this, font);
	info.hide();

	// Game How To Container
	sf::Text* curText = nullptr;
	size = howTo->getSize();
	pos = howTo->getPosition();
	howTo->addText("How To Play", font, headerFontSize - 5);
	curText = &howTo->getTextAt(0);
	curText->setPosition(pos.x + (int)(size.x / 2 - curText->getGlobalBounds().width / 2), pos.y + 5);
	std::string txt = "Create an if-statement that matches the range that will appear on the left using\n"
		"the buttons that will show up below. The top row of buttons will be for the\n"
		"threshold value. This is the value that will line up with the range's circle. If the\n"
		"circle is filled in (closed), then you want to include the threshold value using an\n"
		"operator that has an equal sign ('<=', '>=', '=='). If the circle is empty (open),\n"
		"then you want to exclude the threshold value using one of the other operators\n"
		"('<', '>', or '!='). To figure out which operator to use, keep in mind that you want\n"
		"to include the blue side, and exclude the red side. You should also know what\n"
		"each operator means:\n"
		"\t\t'<' : Less Than\t\t\t   '<=' : Less Than OR Equal To\n"
		"\t\t'>' : Greater Than\t\t   '>= : Greater Than OR Equal To\n"
		"\t\t'!=' : NOT Equal To\t\t '==' : Equal To\n"
		"There are 20 levels. The line starts slow but gets progressively faster. You get\n"
		"3 lives, so think carefully! Keep practicing until you master this game before\n"
		"moving on to the more difficult games. Good luck, you got this!";
	howTo->addText(txt, font, 17);
	curText = &howTo->getTextAt(1);
	curText->setPosition(pos.x + 10, pos.y + 40);
}


/* Screen overrides */

void IfGame::clickButton(int id) {
	// Start Game button
	if (id == 0) {
		startGame();
		return;
	} 

	if (!gameInProgress)
		return;

	// Submit answer button
	if (id == 1) {
		submitAnswer();
		return;
	}

	// Threshold buttons
	if (id >= 2 && id <= 13) {
		std::string txt = choiceButtons->getButtonAt(id - 2).getText();

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
	Logger::log("Clicked button with ID " + std::to_string(id) + "\n");
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
		Logger::log("Answer Line has reached the bottom\n");
		submitAnswer();
	}
	else {
		answerLine.dropDown(dt);
	}
}

void IfGame::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!active)
		return;

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

	choiceButtons->addButton("", buttonID, sf::Vector2f(posX, posY), size, font);
	curButton = &choiceButtons->getButtonAt(buttonID - 2);
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
		choiceButtons->getButtonAt(index).setText(buttonText);

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
		choiceButtons->getButtonAt(index).setText(buttonText);
	}
}

void IfGame::populateNumberLine() {
	if (lowerBound < -99 || lowerBound > 84) {
		Logger::log("Bounds not set properly, can't populate number line.\n");
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
		Logger::log("Correct!\n");
		onCorrect();
		score++;
		info.updateScore(score);
	}
	else {
		Logger::log("Wrong!\n");
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
	Logger::log("Moving on to level " + std::to_string(currentLevel) + "\n");
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
	Logger::log("Starting game!\n");

	// Hide the start button
	buttons.at(0).hide();

	// Show all the answer choice buttons
	containers.at(1).show();
	buttons.at(1).show();

	currentLevel = 1;
	info.updateLevel(currentLevel);
	score = 0;
	info.updateScore(score);
	info.updateHighScore(Logger::getHighScore());
	lives = 3;
	info.updateLives(lives);
	info.setOutlineColor(Screen::defaultBorder);
	info.show();
	choiceButtons->show();
	startRound();
}

void IfGame::endGame(bool finished) {
	gameInProgress = false;

	if (finished) {
		Logger::log("You won with a score of " + std::to_string(score) + "!\n");
	}
	else {
		Logger::log("You lost... You made it to level " + std::to_string(currentLevel));
		Logger::log(" with a score of " + std::to_string(score) + "...\n");
	}

	int oldHighScore = Logger::getHighScore();
	if (score > oldHighScore) {
		info.updateHighScore(score);
		Logger::setHighScore(score);
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
	playArea->setOutlineColor(color);
	howTo->setOutlineColor(color);
	choiceButtons->setOutlineColor(color);
}

void IfGame::onCorrect() { changeOutlineColors(Screen::trueColor); }

void IfGame::onWrong() { changeOutlineColors(Screen::falseColor); }

void IfGame::reset() {
	answerLine.reset();
	answerText.reset();
	answerText.show();
	info.setOutlineColor(Screen::defaultBorder);
	playArea->setOutlineColor(Screen::defaultBorder);
	howTo->setOutlineColor(Screen::defaultBorder);
	choiceButtons->setOutlineColor(Screen::defaultBorder);
}

void IfGame::init() {
	reset();
	answerLine.resetSpeed();
	answerText.hide();
	info.hide();
	info.reset();
	choiceButtons->hide();
	buttons.at(1).hide();
	buttons.at(0).show();
}