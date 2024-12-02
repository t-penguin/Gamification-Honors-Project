#include "AnswerText.h"

AnswerText::AnswerText() { }

AnswerText::AnswerText(sf::Font& font) {
	parent = nullptr;
	texts.reserve(1);
	addText("", font, 20);
}