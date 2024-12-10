#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

class Logger {
	private:
		static std::ifstream readScore;
		static std::ofstream writeScore;
		static std::ofstream writeLog;
	public:
		Logger() = delete;

		static void init();
		static void log();
		static void setHighScore();
		static int getHighScore();
};

#endif