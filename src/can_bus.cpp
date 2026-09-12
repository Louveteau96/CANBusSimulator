#include "can_bus.hpp"
#include "can_logger.hpp"
#include <iostream>

//Constructeur
CANBus::CANBus(CANLogger& logger) : logger(logger){};

void CANBus::send(const CANMessage& msg) {
    std::lock_guard<std::mutex> lock(queueMutex);
	//Envoi du message sur le CAN
    messageQueue.push(msg);
	//Ajout au log
	logger.debug ("Message envoyé - ID: 0x" + std::to_string(msg.id) +
					", Data size : " + std::to_string(msg.data.size()));

	// Reveille un thread en attente
    condVar.notify_one();
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

	//Ajout au log
	logger.debug("Message reçu - ID: 0x" + std::to_string(msg.id));
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