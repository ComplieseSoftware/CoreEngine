#include <fstream>
#include <string>
#include <string_view>
#include <iostream>
#include <ctime>
#include <mutex>

#include "Logger.h"

namespace Logger {
	namespace {
		#define RESET   "\033[0m"
		#define RED     "\033[31m"
		#define GREEN   "\033[32m"
		#define YELLOW  "\033[33m"
		#define BLUE    "\033[34m"
		#define BG_RED    "\033[41m"

		std::string logFile{ "CoreEngineLogs.txt" };
		std::ofstream logOut{ logFile, std::ios::app };
		bool isNeedTime{};

		std::mutex logMutex{};

		std::string getTime() {
			if (!isNeedTime) {
				return "";
			}

			std::time_t now{ std::time(nullptr) };
			std::tm localTime{};

			localtime_s(&localTime, &now);

			return "[" + std::to_string(1900 + localTime.tm_year) + "-"
				+ std::to_string(1 + localTime.tm_mon) + "-"
				+ std::to_string(localTime.tm_mday) + " "
				+ std::to_string(localTime.tm_hour) + ":"
				+ std::to_string(localTime.tm_min) + ":"
				+ std::to_string(localTime.tm_sec) + "] ";
		}
	}

	void init(const std::string_view fileName, bool needTime) {
		std::lock_guard<std::mutex> lock(logMutex);

		if (fileName.empty()) {
			std::cout << YELLOW << "We can't find name of log's file, so we will use default log's file: " << logFile << RESET << "\n";
			isNeedTime = needTime;
		}
		else {
			logFile = fileName;
			isNeedTime = needTime;

			std::cout << "New log's file is " << fileName << "\n";
			std::cout << "Are we need to point current time: " << isNeedTime << "\n";
		}

		if (logOut.is_open()) {
			logOut.close();
		}

		logOut.open(logFile, std::ios::app);

		if (!logOut.is_open()) {
			std::cout << RED << "Core Engine can't open log's file. Please restart your computer and try again\n" << RESET;
			std::cerr << BG_RED << "Close Core Engine\n" << RESET;
		}
	}

	void info(std::string_view message) {
		std::lock_guard<std::mutex> lock(logMutex);

		if (!message.empty()) {
			if (!logOut.is_open()) {
				std::cout << RED << "Core Engine can't open log's file. Please restart your computer and try again\n" << RESET;
				std::cerr << BG_RED << "Close Core Engine\n" << RESET;
				return;
			}

			std::string timeStr = getTime();

			std::cout << RESET << timeStr << message << "\n";
			logOut << timeStr << "[INFO]" << message << "\n";

			logOut.flush();
		}
		else {
			std::cout << RED << "You need to write a message!\n" << RESET;
		}
	}

	void warn(std::string_view message) {
		std::lock_guard<std::mutex> lock(logMutex);
		
		if (!message.empty()) {
			if (!logOut.is_open()) {
				std::cout << RED << "Core Engine can't open log's file. Please restart your computer and try again\n" << RESET;
				std::cerr << BG_RED << "Close Core Engine\n" << RESET;
				return;
			}

			std::string timeStr = getTime();

			std::cout << YELLOW << timeStr << message << "\n";
			logOut << timeStr << "[WARN]" << message << "\n";

			logOut.flush();
		}
		else {
			std::cout << RED << "You need to write a message!\n" << RESET;
		}
	}

	void error(std::string_view message) {
		std::lock_guard<std::mutex> lock(logMutex);
		
		if (!message.empty()) {
			if (!logOut.is_open()) {
				std::cout << RED << "Core Engine can't open log's file. Please restart your computer and try again\n" << RESET;
				std::cerr << BG_RED << "Close Core Engine\n" << RESET;
				return;
			}

			std::string timeStr = getTime();

			std::cout << RED << timeStr << message << "\n";
			logOut << timeStr << (isNeedTime ? "[ERROR] - " : "") << message << "\n";

			logOut.flush();
		}
		else {
			std::cout << RED << "You need to write a message!\n" << RESET;
		}
	}

	void fatal(std::string_view message) {
		std::lock_guard<std::mutex> lock(logMutex);
		
		if (!message.empty()) {
			if (!logOut.is_open()) {
				std::cout << RED << "Core Engine can't open log's file. Please restart your computer and try again\n" << RESET;
				std::cerr << BG_RED << "Close Core Engine\n" << RESET;
				return;
			}

			std::string timeStr = getTime();

			std::cout << BG_RED << timeStr << message << "\n";
			logOut << timeStr << "[FATAL]" << message << "\n";

			logOut.flush();
		}
		else {
			std::cout << RED << "You need to write a message!\n" << RESET;
		}
	}
}