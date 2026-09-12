// tests/can_logger_test.cpp
#include "unity.h"
#include "../src/can_logger.hpp"
#include "../src/can_bus.hpp"
#include <fstream>
#include <string>

void test_CANLogger_FileCreation(void) {
    CANLogger logger("log/test_log.log", LogLevel::DEBUG);
    logger.info("Test message");
    TEST_ASSERT_TRUE(std::ifstream("log/test_log.log").good());
}

void test_CANLogger_LogLevels(void) {
    CANLogger logger("log/test_log_levels.log", LogLevel::WARNING);
    logger.debug("Debug message"); // Ne devrait pas être logué
    logger.info("Info message");   // Ne devrait pas être logué
    logger.warning("Warning message"); // Devrait être logué
    logger.error("Error message");     // Devrait être logué

    std::ifstream file("log/test_log_levels.log");
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    TEST_ASSERT_TRUE(content.find("Warning message") != std::string::npos);
    TEST_ASSERT_TRUE(content.find("Error message") != std::string::npos);
    TEST_ASSERT_TRUE(content.find("Debug message") == std::string::npos);
}

void test_CANLogger_TimestampFormat(void) {
    CANLogger logger("log/test_timestamp.log", LogLevel::DEBUG);
    logger.info("Test timestamp");
    std::ifstream file("log/test_timestamp.log");
	TEST_ASSERT_TRUE(file.is_open());
    std::string line;
    std::getline(file, line);
	TEST_ASSERT_TRUE(!line.empty());

    // Vérifier que le timestamp a le format "YYYY-MM-DD HH:MM:SS.mmm"
    TEST_ASSERT_TRUE(line.find("-") != std::string::npos);	//Vérifie séparateur de date
	TEST_ASSERT_TRUE(line.find(":") != std::string::npos);	//Vérifie séparateur d'heures 
    TEST_ASSERT_TRUE(line.find(".") != std::string::npos); // Vérifie séparateur de millisecondes
}