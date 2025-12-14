#ifndef ALARMHANDLER_H
#define ALARMHANDLER_H

#include "EmergencyHandler.h"
#include <iostream>
#include <thread>
#include <chrono>

// Handles the alarm state in the emergency sequence.
class AlarmHandler : public EmergencyHandler {
public:
    void handleRequest() override {
        cout << "[Sistem] Alarm 10 saniye boyunca aktif..." << endl;
        
        // Simulates alarm duration. Blocking wait for initial implementation.
        cout << "[Sistem] Alarmı durdurmak için 's' tuşuna, devam etmek için başka bir tuşa basınız..." << endl;
        char input;
        cout << "> ";
        cin >> input;

        if (input == 's' || input == 'S') {
            cout << "[Sistem] Alarm kullanıcı tarafından durduruldu. Zincir kesildi." << endl;
        } else {
            cout << "[Sistem] Müdahale yok. Bir sonraki adıma geçiliyor..." << endl;
            EmergencyHandler::handleRequest();
        }
    }
};

#endif
