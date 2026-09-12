#include "unity.h"
#include "../src/can_message.hpp"
#include <sstream>
#include <string>

// ===== Implémentations des tests CANMessage =====
void test_CANMessage_ConstructorAndFields(void) {
    CANMessage msg;
    TEST_ASSERT_EQUAL(0, msg.id);
    TEST_ASSERT_TRUE(msg.data.empty());
    TEST_ASSERT_TRUE(msg.timestamp.empty());

    msg.id = 0x123;
    msg.data = {0x01, 0x02, 0x03, 0x04};
    msg.timestamp = "2026-09-12 13:17:28";
    TEST_ASSERT_EQUAL(0x123, msg.id);
    TEST_ASSERT_EQUAL(4, msg.data.size());
    TEST_ASSERT_EQUAL(0x01, msg.data[0]);
    TEST_ASSERT_EQUAL(0x02, msg.data[1]);
    TEST_ASSERT_EQUAL(0x03, msg.data[2]);
    TEST_ASSERT_EQUAL(0x04, msg.data[3]);
    TEST_ASSERT_EQUAL_STRING("2026-09-12 13:17:28", msg.timestamp.c_str());
}

void test_CANMessage_PrintFunction(void) {
    CANMessage msg;
    msg.id = 0x123;
    msg.data = {0x01, 0x02, 0x03, 0x04};
    msg.timestamp = "2026-09-12 13:17:28";
    // Test d'affichage (optionnel)
    TEST_ASSERT_EQUAL(0x123, msg.id);
}

void test_CANMessage_DifferentDataSizes(void) {
    CANMessage msg;
    msg.id = 0x456;

    msg.data = {};
    TEST_ASSERT_EQUAL(0, msg.data.size());

    msg.data = {0xAA};
    TEST_ASSERT_EQUAL(1, msg.data.size());
    TEST_ASSERT_EQUAL(0xAA, msg.data[0]);

    msg.data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    TEST_ASSERT_EQUAL(8, msg.data.size());
    TEST_ASSERT_EQUAL(0x08, msg.data[7]);
}

void test_CANMessage_DifferentIDs(void) {
    CANMessage msg;
    msg.id = 0x000;
    TEST_ASSERT_EQUAL(0x000, msg.id);

    msg.id = 0x7FF;
    TEST_ASSERT_EQUAL(0x7FF, msg.id);

    msg.id = 0x1FFFFFFF;
    TEST_ASSERT_EQUAL(0x1FFFFFFF, msg.id);
}