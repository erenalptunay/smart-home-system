#include "SecuritySystem.h"
#include <iostream>

SecuritySystem::SecuritySystem(Alarm* alarm, const std::vector<Device*>& allDevices) {
    // 1. Concrete Handler'larý oluþtur
    alarmHandler_ = new AlarmHandler(alarm);
    lightOnHandler_ = new LightOnHandler(allDevices);
    policeCallHandler_ = new PoliceCallHandler();

    // 2. Chain of Responsibility zincirini kur (LLR-13)
    // Alarm -> Light On -> Police Call
    alarmHandler_
        ->setNext(lightOnHandler_)
        ->setNext(policeCallHandler_);

    std::cout << "[SecuritySystem] Chain initialized: Alarm -> Light -> Police" << std::endl;
}

SecuritySystem::~SecuritySystem() {
    // Bellek sýzýntýsýný önlemek için handler'larý sil
    delete alarmHandler_;
    delete lightOnHandler_;
    delete policeCallHandler_;
}

void SecuritySystem::onMotionDetected() {
    std::cout << "[SecuritySystem] Starting sequence (Motion Detected)..." << std::endl;
    // Zinciri baþlatmak için ilk halkayý çaðýr
    alarmHandler_->handleRequest(SecurityEvent::MotionDetected);

    // LLR-37: Zincir bittikten sonra sistem yeni hareket algýlamaya hazýr olmalýdýr.
    std::cout << "[SecuritySystem] Ready for next event." << std::endl;
}