#include "can_bus.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <mutex>

// Mutex pour synchroniser l'affichage
std::mutex coutMutex;

// Fonction pour generer un timestamp
std::string getCurrentTimeStamp() {
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

int main() {
    CANBus bus;
    bus.start();

    // Thread emetteur
    std::thread senderThread([&bus]() {
        for (int i = 0; i < 5; i++) {
            CANMessage msg;
            msg.id = 0x123;
            msg.data = {0x01, 0x02, 0x03, (uint8_t)i};
            msg.timestamp = getCurrentTimeStamp();
            bus.send(msg);

            // Synchronisation de l'affichage
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Sender: Message envoye (ID=0x" << std::hex << msg.id << std::dec << ")" << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    // Thread recepteur
    std::thread receiverThread([&bus]() {
        for (int i = 0; i < 5; i++) {
            CANMessage msg = bus.receive();

            // Synchronisation de l'affichage
            std::lock_guard<std::mutex> lock(coutMutex);
            msg.print();
        }
    });

    // Attend la fin des threads
    senderThread.join();
    receiverThread.join();

    bus.stop();

    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << "Simulation terminee." << std::endl;

    return 0;
}