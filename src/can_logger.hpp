//can_logger.hpp
#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <stdexcept>

enum class LogLevel{
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

class CANLogger {
	public:
	//Constructeur : fichier de log + LogLevel
	CANLogger(const std::string& filename, LogLevel minLevel = LogLevel::INFO);

	//Méthode de log
	void log(LogLevel level, const std::string& message);
	void debug(const std::string& message);
	void info(const std::string& message);
	void warning(const std::string& message);
	void error(const std::string& message);
	void critical(const std::string& message);

	//Ferme de logger
	~CANLogger();

	private:
	std::ofstream logFile;
	LogLevel minLevel;
	std::mutex logMutex; // Pour la thread-safety

	// Générer un timestamp
    std::string getTimestamp();

	// Convertir LogLevel en string
    std::string levelToString(LogLevel level);

};