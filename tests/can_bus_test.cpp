#include "unity.h"
#include "../src/can_bus.hpp"
#include <thread>
#include <chrono>
#include <vector>

// bus est déclarée dans test_runner.cpp (globale)
extern CANBus bus;

// ===== Implémentations des tests CANBus =====
void test_CANBus_SendAndReceive(void) {
    CANMessage msg;
    msg.id = 0x123;
    msg.data = {0x01, 0x02, 0x03, 0x04};
    msg.timestamp = "2026-09-12 13:17:28";
    bus.send(msg);
    CANMessage received = bus.receive();
    TEST_ASSERT_EQUAL(msg.id, received.id);
    TEST_ASSERT_EQUAL(msg.data.size(), received.data.size());
    for (size_t i = 0; i < msg.data.size(); i++) {
        TEST_ASSERT_EQUAL(msg.data[i], received.data[i]);
    }
    TEST_ASSERT_EQUAL_STRING(msg.timestamp.c_str(), received.timestamp.c_str());
}

void test_CANBus_MultipleMessages(void) {
    for (int i = 0; i < 5; i++) {
        CANMessage msg;
        msg.id = 0x100 + i;
        msg.data = {(uint8_t)i, (uint8_t)(i+1)};
        msg.timestamp = "2026-09-12 13:17:" + std::to_string(30 + i);
        bus.send(msg);
    }

    for (int i = 0; i < 5; i++) {
        CANMessage received = bus.receive();
        TEST_ASSERT_EQUAL(0x100 + i, received.id);
        TEST_ASSERT_EQUAL((uint8_t)i, received.data[0]);
        TEST_ASSERT_EQUAL((uint8_t)(i+1), received.data[1]);
    }
}

void test_CANBus_StartAndStop(void) {
    bus.stop();
    TEST_ASSERT_FALSE(bus.isRunning());
    bus.start();
    TEST_ASSERT_TRUE(bus.isRunning());
}

void test_CANBus_Concurrency(void) {
    const int NUM_MESSAGES = 10;
    std::vector<std::thread> senders;
    std::vector<std::thread> receivers;
    std::vector<CANMessage> receivedMessages(NUM_MESSAGES);

    for (int i = 0; i < NUM_MESSAGES; i++) {
        senders.emplace_back([i]() {
            CANMessage msg;
            msg.id = 0x200 + i;
            msg.data = {(uint8_t)i};
            msg.timestamp = "2026-09-12 13:18:" + std::to_string(i);
            bus.send(msg);
        });
    }

    for (int i = 0; i < NUM_MESSAGES; i++) {
        receivers.emplace_back([&receivedMessages, i]() {
            receivedMessages[i] = bus.receive();
        });
    }

    for (auto& sender : senders) sender.join();
    for (auto& receiver : receivers) receiver.join();

    for (int i = 0; i < NUM_MESSAGES; i++) {
        bool found = false;
        for (const auto& msg : receivedMessages) {
            if (msg.id == static_cast<uint32_t>(0x200 + i)) {
                found = true;
                break;
            }
        }
        TEST_ASSERT_TRUE(found);
    }
}