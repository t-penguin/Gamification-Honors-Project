#include "MainScreen.h"

MainScreen::MainScreen() { }
MainScreen::MainScreen(sf::RenderWindow& window, sf::Font& font) {
	gameIndex = -1;

	sf::Vector2u screenSize = window.getSize();
	sf::Vector2u screenMiddle(screenSize.x / 2, screenSize.y / 2);
	sf::Vector2f size;
	sf::Vector2f pos;

	// Header Text
	addText("Welcome To\nGamification!", font, 30);
	texts.at(0).setPosition((int)(screenMiddle.x - texts.at(0).getGlobalBounds().width / 2), 15);

	// Application Description Container
	size.x = 450;
	size.y = 500;
	pos.x = 20;
	pos.y = 110;
	addContainer(size, pos);
	descriptionText = &containers.at(0);

	// If Game Selection Container
	size.x = 700;
	size.y = 150;
	pos.x = 500;
	addContainer(size, pos);
	ifGameSummary = &containers.at(1);

	// Switch Game Selection Container
	pos.y = 280;
	addContainer(size, pos);
	switchGameSummary = &containers.at(2);

	sf::Text* curText = nullptr;
	// Application desciption
	descriptionText->addText("What Is This??", font, 25);
	curText = &descriptionText->getTextAt(0);
	curText->setPosition(descriptionText->getPosition().x + 10, descriptionText->getPosition().y + 5);
	
	std::string txt =
		"Gamification is my contribution to education accessibility.\n"
		"It aims to turn educational topics from a range of subjects\n"
		"into games that help you visualize and understand the\n"
		"concepts better! Everyone learns differently, so there is\n"
		"no general solution to education. This program is not\n"
		"meant to replace your education, but rather to supplement\n"
		"it. Don't be discouraged if this program doesn't help you\n"
		"understand some or all of the included concepts. In that\n"
		"case, you should look for something else that does!\n\n"
		"To get started with the app, find a game on the right that\n"
		"matches the topic you want to practice.";
	descriptionText->addText(txt, font, 17);
	curText = &descriptionText->getTextAt(1);
	curText->setPosition(descriptionText->getPosition().x + 10, descriptionText->getPosition().y + 35);

	descriptionText->addText("Who Am I??", font, 25);
	curText = &descriptionText->getTextAt(2);
	curText->setPosition(descriptionText->getPosition().x + 10, descriptionText->getPosition().y + 300);

	txt =
		"Hey! I'm Joseph! At the time of making this, I am a\n"
		"Computer Science student at BMCC. This application is\n"
		"my honors project for my Advanced Programming\n"
		"Techniques class with Dr. Azhar. I've always been\n"
		"interested in games and making them, as well as helping\n"
		"people with math and science, so I figured why not do\n"
		"both! I hope you enjoy the games and get better at\n"
		"understanding more concepts!";

	descriptionText->addText(txt, font, 17);
	curText = &descriptionText->getTextAt(3);
	curText->setPosition(descriptionText->getPosition().x + 10, descriptionText->getPosition().y + 330);

	// If-Statement Game Text and Button
	ifGameSummary->addText("Match The Range", font, 25);
	curText = &ifGameSummary->getTextAt(0);
	curText->setPosition(ifGameSummary->getPosition().x + 10, ifGameSummary->getPosition().y + 5);

	txt =
		"Waves of people are approaching my fortress and I need your help figuring out who to let\n"
		"in. I have these special goggles that show our allies in blue and enemies in red, but\n"
		"wearing it gives me a headache. Do you think you can put it on and help me? I'll show you\n"
		"what to press to let in the right people. It's helpful that they're all wearing numbers...\n";
	ifGameSummary->addText(txt, font, 17);
	curText = &ifGameSummary->getTextAt(1);
	curText->setPosition(ifGameSummary->getPosition().x + 10, ifGameSummary->getPosition().y + 35);

	txt =
		"Categories: If-Statements, Number Lines, Ranges";
	ifGameSummary->addText(txt, font, 17);
	curText = &ifGameSummary->getTextAt(2);
	curText->setPosition(ifGameSummary->getPosition().x + 10, ifGameSummary->getPosition().y + 120);

	size.x = 50;
	size.y = 35;
	pos.x = ifGameSummary->getPosition().x + ifGameSummary->getSize().x - size.x - 10;
	pos.y = ifGameSummary->getPosition().y + ifGameSummary->getSize().y - size.y - 10;
	ifGameSummary->addButton("Play", 0, pos, size, font);

	descriptionText->show();
	ifGameSummary->show();
	switchGameSummary->show();
}

int MainScreen::getGameIndex() const { return gameIndex; }
void MainScreen::resetGameIndex() { gameIndex = -1; }

void MainScreen::clickButton(int buttonID) {
	gameIndex = buttonID;
}