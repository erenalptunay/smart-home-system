#include "PoliceCallHandler.h"
#include <iostream>
#include <chrono>
#include <thread>

void PoliceCallHandler::handleRequest(SecurityEvent event) {
    if (event == SecurityEvent::MotionDetected) {
        std::cout << "\n--- [Security Step 3] PoliceCallHandler activated. ---" << std::endl;

        // LLR-35: Polisi arama mesajýný yazdýrma (Zincirin sonu)
        std::cout << ">>> System displays: \"A call is placed to Police.\"" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "--- SECURITY SYSTEM SEQUENCE END ---" << std::endl;

        // Bu zincirin sonudur, BaseHandler::handleRequest çaðrýlmaz.
    }
    else {
        BaseHandler::handleRequest(event);
    }
}