#include "../include/security_system/AlarmHandler.h"
#include <iostream>
#include <thread>
#include <chrono>

AlarmHandler::AlarmHandler() {
	alarmInstance_ = Alarm::getInstance();
}

void AlarmHandler::handleRequest(SecurityEvent event) {
	if (event == SecurityEvent::MotionDetected) {
		std::cout << "\n--- [ADIM 1] AlarmHandler Devrede ---" << std::endl;

		if (alarmInstance_) alarmInstance_->connect();

		// --- DEÐÝÞÝKLÝK BURADA: 3 yerine 5 yaptýk ---
		std::cout << "   -> Alarm 5 saniye boyunca caliyor..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));

		if (alarmInstance_) alarmInstance_->close();

		if (nextHandler) {
			std::cout << "   -> Alarm bitti, sira Isiklarda..." << std::endl;
			nextHandler->handleRequest(event);
		}
	}
	else {
		BaseHandler::handleRequest(event);
	}
}