#pragma once
#include "can_message.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

class CANBus {
    public:
        // Envoie un message sur le bus
        void send(const CANMessage& msg);

        // Recoit un message du bus (bloquant)
        CANMessage receive();

        // Demarre le bus (simulation)
        void start();

        // Arrete le bus
        void stop();

        // Verifie si le bus est en cours d'execution
        bool isRunning() const;

    private:
        std::queue<CANMessage> messageQueue;
        std::mutex queueMutex;
        std::condition_variable condVar;
        bool running = false;
        std::thread busThread;
};