#include "AnswerLine.h"
#include "Screen.h"
#include <cmath>

AnswerLine::AnswerLine(int start, int end, int width, float speed) {
	hide();

	startY = start;
	curHeight = start;
	endY = end;
	this->width = width;
	dotOffset = -5;
	fallSpeed = speed;

	leftSide = sf::RectangleShape();
	leftSide.setPosition(32, startY);
	rightSide = sf::RectangleShape();
	rightSide.setPosition(32, startY);
	dot = sf::CircleShape(6);
	dot.setPosition(32, startY + dotOffset);
	dot.setOutlineColor(Screen::trueColor);
	dot.setOutlineThickness(3);
}

void AnswerLine::setThresholdPosition (const int lowerBound, const int threshold) {
	int leftLength = (threshold - lowerBound) * 42 - 8;
	int rightLength = width - leftLength - 16;

	leftSide.setSize(sf::Vector2f(leftLength, 4));
	rightSide.setSize(sf::Vector2f(rightLength, 4));
	leftSide.setPosition(32, curHeight);
	rightSide.setPosition(48 + leftLength, curHeight);
	dot.setPosition(32 + leftLength + 2, curHeight + dotOffset);
}

void AnswerLine::setBooleanOperator (const BoolOperator op) {
	switch (op)
	{
		case LessThan:
		case LessThanOrEqualTo:
			leftSide.setFillColor(Screen::trueColor);
			rightSide.setFillColor(Screen::falseColor);
			break;
		case GreaterThan:
		case GreaterThanOrEqualTo:
			leftSide.setFillColor(Screen::falseColor);
			rightSide.setFillColor(Screen::trueColor);
			break;
		case EqualTo:
			leftSide.setFillColor(Screen::falseColor);
			rightSide.setFillColor(Screen::falseColor);
			break;
		case NotEqualTo:
			leftSide.setFillColor(Screen::trueColor);
			rightSide.setFillColor(Screen::trueColor);
			break;
	}

	if (op % 2 == 0) {
		dot.setOutlineColor(Screen::trueColor);
		dot.setFillColor(Screen::trueColor);
	}
	else {
		dot.setOutlineColor(Screen::trueColor);
		dot.setFillColor(sf::Color::Transparent);
	}
}

void AnswerLine::dropDown(const float dt) {
	curHeight += fallSpeed * dt;
	leftSide.setPosition(leftSide.getPosition().x, (int)curHeight);
	rightSide.setPosition(rightSide.getPosition().x, (int)curHeight);
	dot.setPosition(dot.getPosition().x, (int)curHeight + dotOffset);
}

void AnswerLine::increaseSpeed(const float speed) { fallSpeed += speed; }

void AnswerLine::reset() {
	hide();
	curHeight = startY;
}

bool AnswerLine::getToDraw() const { return toDraw; }

bool AnswerLine::isAtBottom() const { return curHeight >= endY; }

void AnswerLine::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!toDraw)
		return;

	target.draw(leftSide, states);
	target.draw(rightSide, states);
	target.draw(dot, states);
}