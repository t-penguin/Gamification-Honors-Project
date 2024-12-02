#ifndef IFANSWERTEXT_H
#define IFANSWERTEXT_H

#include "AnswerText.h"

class IfAnswerText : public AnswerText {
	private:
		static int defaultThreshold;

		std::string threshold;
		std::string boolOp;
	public:
		IfAnswerText();
		IfAnswerText(sf::Font& font);
		void setThreshold(const std::string thresholdText);
		void setBoolOperator(const std::string boolOpText);
		void setOutlineColor(const sf::Color& color);
		void reset();
		void setText() override;
};

#endif