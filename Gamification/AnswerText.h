#ifndef ANSWERTEXT_H
#define ANSWERTEXT_H

#include "Container.h"
#include <string>

class AnswerText : public Container {
	public:
		AnswerText();
		AnswerText(sf::Font& font);
		virtual void setText() = 0;
};

#endif

