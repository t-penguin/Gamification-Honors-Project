#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

class Logger {
	private:
		static std::string scoreFile;
		static std::string logFile;
	public:
		Logger() = delete;

		static void init();
		static void log(std::string msg);
		static void setHighScore(int score);
		static int getHighScore();
};

#endif