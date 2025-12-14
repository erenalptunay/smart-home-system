#include "../include/security_system/PoliceCallHandler.h"
#include <iostream>

void PoliceCallHandler::handleRequest(SecurityEvent event) { // gelen olaya bakarak polisi arar.
	if (event == SecurityEvent::MotionDetected) {
		std::cout << "\n--- PoliceCallHandler Devrede ---" << std::endl;
		std::cout << ">>> A CALL ÝS PLACED TO POLÝCE.... <<<" << std::endl;
		std::cout << "--- GUVENLIK ZINCIRI TAMAMLANDI ---" << std::endl;
	}
	else {
		BaseHandler::handleRequest(event);
	}
}