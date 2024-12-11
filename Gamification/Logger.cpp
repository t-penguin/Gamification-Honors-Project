#include "Logger.h"

std::string Logger::scoreFile = "score.txt";
std::string Logger::logFile = "log.txt";

void Logger::init() {
	std::ofstream logOut(logFile, std::ios::out | std::ios::app);
	if (!logOut.is_open())
		std::cout << "Could not open log file for writing.";
	else {
		log("\n-------------- New Session --------------\n");
	}
	logOut.close();

	std::ifstream scoreIn(scoreFile);
	if (!scoreIn.is_open()) {
		std::ofstream scoreOut(scoreFile, std::ios::out);
		scoreOut << "0";
		scoreOut.close();
	}
	scoreIn.close();
}

void Logger::log(std::string msg) {
	std::ofstream logOut(logFile, std::ios::app);

	if (logOut.is_open()) {
		logOut << msg;
	}

	logOut.close();

	std::cout << msg;
}

void Logger::setHighScore(int score) {
	std::ofstream scoreOut(scoreFile, std::ios::out);

	if (scoreOut.is_open()) {
		log("Setting new high score\n");
		scoreOut << score << "\n";
	}
	
	scoreOut.close();

	log("New high score: " + std::to_string(score) + "!\n");
}

int Logger::getHighScore() {
	std::ifstream scoreIn(scoreFile, std::ios::in);

	if (scoreIn.is_open()) {
		int score;
		scoreIn >> score;
		scoreIn.close();
		return score;
	}

	

	return -1;
}