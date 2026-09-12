#include "can_bus.hpp"
#include <iostream>

void CANBus::send(const CANMessage& msg) {
    std::lock_guard<std::mutex> lock(queueMutex);
    messageQueue.push(msg);
    condVar.notify_one();   // Reveille un thread en attente
}

CANMessage CANBus::receive() {
    std::unique_lock<std::mutex> lock(queueMutex);

    // Attend qu'il y ait un message ou que le bus soit arrete
    condVar.wait(lock, [this] { return !messageQueue.empty() || !running; });

    // Si le bus est arrete et qu'il n'y a plus de messages, retourne un message vide
    if (!running && messageQueue.empty()) {
        return CANMessage{0, {}, ""};
    }

    CANMessage msg = messageQueue.front();
    messageQueue.pop();
    return msg;
}

void CANBus::start() {
    running = true;
    busThread = std::thread([this]() {
        // Simulation d'un bus reel
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
}

void CANBus::stop() {
    running = false;
    condVar.notify_all(); // Reveille tous les threads en attente
    if (busThread.joinable()) {
        busThread.join();
    }
}

bool CANBus::isRunning() const {
    return running;
}