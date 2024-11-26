#include "IfGame.h"
#include <iostream>

/* Constructors */

IfGame::IfGame() { }
IfGame::IfGame(sf::RenderWindow& window, sf::Font& font) {
	gameInProgress = false;

	// Reserve space for vectors to avoid resizing and copying during runtime
	buttons.reserve(15);
	texts.reserve(20);
	sprites.reserve(5);
	shapes.reserve(10);

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
	texts.at(0).setPosition((int)(screenMiddle.x - texts.at(0).getGlobalBounds().width / 2), 20);

	// Start button
	sf::Vector2f buttonSize(100, 35);
	sf::Vector2f buttonPos((int)(screenMiddle.x - buttonSize.x / 2), (int)(screenSize.y - buttonSize.y - 20));
	addButton("Start Game", buttonPos, buttonSize, font);

	// Play area background
	sf::Shape* shapePtr = new sf::RectangleShape(sf::Vector2f(615, 575));
	shapePtr->setOutlineThickness(3);
	shapePtr->setOutlineColor(yellow);
	shapePtr->setFillColor(sf::Color(20, 20, 20));
	shapePtr->setPosition(sf::Vector2f(20, 70));
	addShape(shapePtr);

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

	// Green line shape, size and position changed later
	shapePtr = new sf::RectangleShape();
	shapePtr->setFillColor(green);
	addShape(shapePtr);

	// Red line shape, size and position changed later
	shapePtr = new sf::RectangleShape();
	shapePtr->setFillColor(red);
	addShape(shapePtr);

	// Green circle shape, position and fill color changed later
	shapePtr = new sf::CircleShape(6);
	shapePtr->setOutlineColor(green);
	shapePtr->setOutlineThickness(3);
	addShape(shapePtr);

	// Answer choice buttons container
	sf::Vector2f buttonContainerPos(screenSize.x * 3 / 4 - 185, screenSize.y / 2 + 95);
	shapePtr = new sf::RectangleShape(sf::Vector2f(370, 100));
	shapePtr->setOutlineThickness(3);
	shapePtr->setOutlineColor(yellow);
	shapePtr->setFillColor(sf::Color(20, 20, 20));
	shapePtr->setPosition(buttonContainerPos);
	addShape(shapePtr);

	// Answer choice buttons
	int buttonID = 1;
	sf::Vector2f size(50, 35);
	sf::Vector2f offset(17, 7);
	thresholdOptionIndexes = std::vector<int>();
	operatorOptionIndexes = std::vector<int>();
	for (int i = 0; i < 6; i++) {
		int posX = (buttonContainerPos.x + 10) + ((size.x + 10) * i);
		int posY = screenSize.y / 2 + 105;
		addButton("", sf::Vector2f(posX, posY), size, font);
		buttons.at(buttonID).setTextOffset(offset);
		thresholdOptionIndexes.push_back(buttonID);
		buttonID++;
		posY += size.y + 10;
		addButton("", sf::Vector2f(posX, posY), size, font);
		buttons.at(buttonID).setTextOffset(offset);
		operatorOptionIndexes.push_back(buttonID);
		buttonID++;
	}
}


/* Destructor */

IfGame::~IfGame() { }


/* Screen overrides */

void IfGame::clickButton(int id) {
	if (id == 0) // Start Game button
		startGame();
	else if (id >= 1 && id <= 12 && gameInProgress) { // Answer choice button
		if (id == thresholdOptionIndexes.at(correctThresholdIndex) || id == operatorOptionIndexes.at(correctOperatorIndex))
			std::cout << "Correct!" << std::endl;
	}
	else // Button with no function
		std::cout << "Clicked button with ID " << id << std::endl;
}


/* Helper functions */

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
		buttons.at(index).setText(buttonText);

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
		buttons.at(index).setText(buttonText);
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
	sf::RectangleShape* leftRect = dynamic_cast<sf::RectangleShape*>(shapes.at(1));
	sf::RectangleShape* rightRect = dynamic_cast<sf::RectangleShape*>(shapes.at(2));
	sf::CircleShape* circle = dynamic_cast<sf::CircleShape*>(shapes.at(3));
	int leftLength = (threshold - lowerBound) * 42 - 8;
	int rightLength = 590 - leftLength - 16;
	int startY = 590;
	switch (boolOp)
	{
		case LessThan:
		case LessThanOrEqualTo:
			leftRect->setFillColor(green);
			rightRect->setFillColor(red);
			break;
		case GreaterThan:
		case GreaterThanOrEqualTo:
			leftRect->setFillColor(red);
			rightRect->setFillColor(green);
			break;
		case EqualTo:
			leftRect->setFillColor(red);
			rightRect->setFillColor(red);
			break;
		case NotEqualTo:
			leftRect->setFillColor(green);
			rightRect->setFillColor(green);
			break;
	}

	leftRect->setSize(sf::Vector2f(leftLength, 4));
	rightRect->setSize(sf::Vector2f(rightLength, 4));
	leftRect->setPosition(32, startY);
	rightRect->setPosition(48 + leftLength, startY);

	circle->setPosition(32 + leftLength + 2, startY - 5);
	if (boolOp % 2 == 0)
		circle->setFillColor(green);
	else
		circle->setFillColor(sf::Color::Transparent);
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
			return "Invalid BoolOperator";
	}
}


/* Public functions */

void IfGame::startGame() {
	std::cout << "Starting game!\n";

	startRound();
}

void IfGame::startRound() {
	gameInProgress = true;

	std::srand(std::time(0));
	lowerBound = std::rand() % 184 - 99;
	threshold = lowerBound + std::rand() % 14 + 1;
	boolOp = (BoolOperator)(std::rand() % 6 + 1);

	correctThresholdIndex = std::rand() % 6;
	correctOperatorIndex = std::rand() % 6;
	std::string buttonText;
	generateChoices();
	populateNumberLine();
	createAnswerLine();
}