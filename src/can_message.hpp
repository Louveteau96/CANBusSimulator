//can_message.hpp
#pragma once
#include <cstdint>
#include <vector>
#include <string>
struct CANMessage {
    uint32_t id = 0;                //Identifiant du message (ex:0x123)
    std::vector<uint8_t> data;  //Données (0 à 8 octets)
    std::string timestamp;      //Horodatage (pour le débogage)

    //Affiche le message (pour le débogage)
    void print() const;
};