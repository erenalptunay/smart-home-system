#include "../include/security_system/PoliceCallHandler.h"
#include <iostream>

void PoliceCallHandler::handleRequest1(SecurityEvent event) { // gelen olaya bakarak polisi arar.
	if (event == SecurityEvent::MotionDetected) {
		std::cout << "\n--- PoliceCallHandler Devrede ---" << std::endl;
		std::cout << ">>> A CALL IS PLACED TO POLICE.... <<<" << std::endl;
		std::cout << "--- GUVENLIK ZINCIRI TAMAMLANDI ---" << std::endl;
	}
	else {
		BaseHandler::handleRequest1(event);
	}
}