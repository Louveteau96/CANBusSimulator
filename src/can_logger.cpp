//can_logger.cpp
#include "can_logger.hpp"
#include <filesystem>

CANLogger::CANLogger(const std::string& filename, LogLevel minLevel) 
	: minLevel (minLevel){
		//Créé le dossier parent si besoin
		std::filesystem::path filepath(filename);
		if(filepath.has_parent_path()){
			std::filesystem::create_directories(filepath.parent_path());
		}


		logFile.open(filename, std::ios::app); //Ouvre le logFile en mode append
		if(!logFile.is_open()){
			throw::std::runtime_error("Impossible d'ouvrir le fichier de log : " + filename);
		}
}


CANLogger::~CANLogger() {
	if (logFile.is_open()) {
		logFile.close();
	}
}

void CANLogger::log(LogLevel level, const std::string& message){
	//Ne log pas si le niveau est trop bas
	if (level < minLevel){return;}

	//Mutex pour éviter la concurence de log
	std::lock_guard<std::mutex> lock(logMutex);
	logFile << "[" << getTimestamp() <<"]"
			<< "[" << levelToString(level) << "]"
			<< message << std::endl;
	
	//Force l'écriture immédiate
	logFile.flush();
}

void CANLogger::debug(const std::string& message) { log(LogLevel::DEBUG, message);}
void CANLogger::info(const std::string& message) { log(LogLevel::INFO, message);}
void CANLogger::warning(const std::string& message) { log(LogLevel::WARNING, message);}
void CANLogger::error(const std::string& message) { log(LogLevel::ERROR, message);}
void CANLogger::critical(const std::string& message) { log(LogLevel::CRITICAL, message);}


std::string CANLogger::getTimestamp(){
	auto now = std::chrono::system_clock::now();
	auto now_time = std::chrono::system_clock::to_time_t(now);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

	std::stringstream ss;
	ss	<< std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S")
		<< "." << std::setfill('0') << std::setw(3) << ms.count();
	return ss.str();
}

std::string CANLogger::levelToString(LogLevel level){
	switch (level)
	{
	case LogLevel::DEBUG:		return "DEBUG";
	case LogLevel::INFO:		return "INFO";
	case LogLevel::WARNING:		return "WARNING";
	case LogLevel::ERROR:		return "ERROR";
	case LogLevel::CRITICAL:	return "CRITICAL";
	default:					return "UNKNOWN";
	}
}