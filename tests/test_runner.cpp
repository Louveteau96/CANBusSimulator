#include "unity.h"
#include "../src/can_bus.hpp"
#include "../src/can_logger.hpp"

// Déclaration des variables globales
CANLogger logger("log/test_log.log", LogLevel::DEBUG);
CANBus bus(logger);

// Déclarations de TOUTES les fonctions de test
//Tests CANBus
void test_CANBus_SendAndReceive(void);
void test_CANBus_MultipleMessages(void);
void test_CANBus_StartAndStop(void);
void test_CANBus_Concurrency(void);

//Tests CANMessage
void test_CANMessage_ConstructorAndFields(void);
void test_CANMessage_PrintFunction(void);
void test_CANMessage_DifferentDataSizes(void);
void test_CANMessage_DifferentIDs(void);

//Tests CANLogger
void test_CANLogger_FileCreation(void);
void test_CANLogger_LogLevels(void);
void test_CANLogger_TimestampFormat(void);

// Fonctions setUp/tearDown (appelées automatiquement par Unity)
void setUp(void) {
    bus.start();
}

void tearDown(void) {
    bus.stop();
}

// Point d'entrée unique pour TOUS les tests
int main(void) {
    UNITY_BEGIN();

    // Tests CANBus
    RUN_TEST(test_CANBus_SendAndReceive);
    RUN_TEST(test_CANBus_MultipleMessages);
    RUN_TEST(test_CANBus_StartAndStop);
    RUN_TEST(test_CANBus_Concurrency);

    // Tests CANMessage
    RUN_TEST(test_CANMessage_ConstructorAndFields);
    RUN_TEST(test_CANMessage_PrintFunction);
    RUN_TEST(test_CANMessage_DifferentDataSizes);
    RUN_TEST(test_CANMessage_DifferentIDs);

	// Tests CANLogger
	RUN_TEST(test_CANLogger_FileCreation);
    RUN_TEST(test_CANLogger_LogLevels);
    RUN_TEST(test_CANLogger_TimestampFormat);

    return UNITY_END();
}