#include "AlarmHandler.h"
#include <iostream>
#include <chrono>
#include <thread>

// C2550/C2511 ÇÖZÜMÜ: Kurucu, üye listesi baþlatýcýsý kullanmalý.
AlarmHandler::AlarmHandler(Alarm* alarm) : alarm_(alarm) {
    // C2550/C2511 hatasý, .h dosyasýnda bildirim doðruysa çözülür.
}

void AlarmHandler::handleRequest(SecurityEvent event) {
    if (event == SecurityEvent::MotionDetected) {
        std::cout << "\n--- [Security Step 1] AlarmHandler activated. ---" << std::endl;

        // C2065 (alarm_ eksik) hatasý .h'de taným yapýldýðý için çözülmüþtür.
        if (alarm_) {
            alarm_->turnOn();
        }
        // ... geri kalan mantýk ...
        std::this_thread::sleep_for(std::chrono::seconds(ALARM_DURATION_SECONDS));
        BaseHandler::handleRequest(event);
    }
    else {
        BaseHandler::handleRequest(event);
    }
}