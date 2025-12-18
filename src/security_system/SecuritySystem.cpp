#include "../include/security_system/SecuritySystem.h"
#include <iostream>

SecuritySystem::SecuritySystem(const std::vector<Device*>& devices) {  // cihazların listesi
    alarmHandler = new AlarmHandlerF();
    lightHandler = new LightOn(devices);
    policeHandler = new PoliceCallHandler();

    // Zinciri kur
    alarmHandler->setNext(lightHandler);
    lightHandler->setNext(policeHandler);
}

SecuritySystem::~SecuritySystem() { // destructor method
    delete alarmHandler;
    delete lightHandler;
    delete policeHandler;
}

void SecuritySystem::update(const std::string& deviceName, const std::string& message) {
    // Sensörden gelen sinyali yakala ve 'Ben bu mesajı aldım' diye ekrana yaz.
    std::cout << "\n[SISTEM] Mesaj Alindi (" << deviceName << "): " << message << endl;

    // Şifre Kontrolü -> Alarm -> Işık -> Polis
    if (message == "MOTION_DETECTED") {            
        cout << " Hareket onaylandi. Zincir baslatiliyor..." << endl;
        alarmHandler->handleRequest1(SecurityEvent::MotionDetected);
    }
}
