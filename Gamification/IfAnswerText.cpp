#include "IfAnswerText.h"
#include "Screen.h"

IfAnswerText::IfAnswerText() {

}

IfAnswerText::IfAnswerText(sf::Font& font) : AnswerText(font) {
	show();

	background = sf::RectangleShape(sf::Vector2f(200, 100));
	background.setFillColor(Screen::containerGray);
	background.setOutlineColor(Screen::blue);
	background.setOutlineThickness(3);
	background.setPosition(820, 545);

	threshold = "???";
	boolOp = "??";
	setText();
}

void IfAnswerText::setThreshold(const std::string thresholdText) {
	threshold = thresholdText;
	setText();
}

void IfAnswerText::setBoolOperator(const std::string boolOpText) {
	boolOp = boolOpText;
	setText();
}

void IfAnswerText::setOutlineColor(const sf::Color& color) { background.setOutlineColor(color); }

void IfAnswerText::reset() {
	threshold = "???";
	boolOp = "??";
	setText();
	background.setOutlineColor(Screen::blue);
}

void IfAnswerText::setText() {
	std::string answer = "if (num ";
	answer += boolOp;
	answer += " ";
	answer += threshold;
	answer += " ) {\n\t...\n}";
	texts.at(0).setString(answer);
	int x = background.getPosition().x + (int)(background.getSize().x / 2) - (int)(texts.at(0).getGlobalBounds().width / 2);
	int y = background.getPosition().y + 10;
	texts.at(0).setPosition(x, y);
}