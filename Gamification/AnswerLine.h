#ifndef ANSWERLINE_H
#define ANSWERLINE_H

#include "Hideable.h"
#include "BoolOperatorNames.h"

class IfGame;
class AnswerLine : public Hideable {
	private:
		int startY;
		int endY;
		float curHeight;
		int width;
		int dotOffset;
		float fallSpeed;
		sf::RectangleShape leftSide;
		sf::RectangleShape rightSide;
		sf::CircleShape dot;
	public:
		AnswerLine(int start = 90, int end = 590, int width = 590, float speed = 20);
		void setThresholdPosition(const int lowerBound, const int threshold);
		void setBooleanOperator(const BoolOperator op);
		void dropDown(const float dt);
		void increaseSpeed(const float increment = 5);
		void reset();

		bool getToDraw() const;
		bool isAtBottom() const;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
