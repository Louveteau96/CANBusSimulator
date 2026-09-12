//can_message.cpp
#include "can_message.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

void CANMessage::print() const {
    std::cout << "CAN Message - ID 0x" << std::hex <<id << std::dec
    << ", DATA: [";

    for (size_t i = 0; i < data.size(); i++){
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];

        //Rajoute un espace entre tout les octets sauf apres le dernier
        if (i < data.size()-1) {
            std::cout << " ";
        }
    }
    std::cout <<"], Timestamp: " << timestamp << std::endl;
}