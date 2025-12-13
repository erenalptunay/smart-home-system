#ifndef ALARM_H // Alarm için benzersiz koruma saðlar giriþ çýkýsýnýn olup olmadýðýný incelemek için
#define ALARM_H

#include "Device.h" 
#include <iostream>

class Alarm : public Device {
public:
    void turnOn() override {
        std::cout << "[Alarm] Audible alarm is activated!" << std::endl;
    }

    // LLR-14: Kapatýlamaz
    void turnOff() override {
        std::cout << "[Alarm] WARNING: Cannot turn off safety alarm via menu." << std::endl;
    }

    void printStatus() const override {
        std::cout << "[Alarm] Status: Operational" << std::endl;
    }

    bool isActive() const override { return true; }
};

#endif // ALARM_H