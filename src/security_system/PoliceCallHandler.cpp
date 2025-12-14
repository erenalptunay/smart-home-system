#include "../include/security_system/PoliceCallHandler.h"
#include <iostream>

void PoliceCallHandler::handleRequest(SecurityEvent event) {
	if (event == SecurityEvent::MotionDetected) {
		std::cout << "\n--- [ADIM 3] PoliceCallHandler Devrede ---" << std::endl;
		std::cout << ">>> CALLING POLICE... <<<" << std::endl;
		std::cout << "--- GUVENLIK ZINCIRI TAMAMLANDI ---" << std::endl;
	}
	else {
		BaseHandler::handleRequest(event);
	}
}