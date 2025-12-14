#include "../include/security_system/LightOnHandler.h"
#include "../include/device_hierarchy/Light.h" // Arkadaþýnýn Light sýnýfý
#include <iostream>
#include <thread>
#include <chrono>

LightOnHandler::LightOnHandler(const std::vector<Device*>& devices) : allDevices_(devices) {}

void LightOnHandler::handleRequest(SecurityEvent event) {
	if (event == SecurityEvent::MotionDetected) {
		std::cout << "\n--- [ADIM 2] LightOnHandler Devrede ---" << std::endl;

		// Gerçekçilik için bekleme
		std::this_thread::sleep_for(std::chrono::seconds(1));

		for (Device* d : allDevices_) {
			// Arkadaþýnýn Light sýnýfýna cast et
			if (Light* l = dynamic_cast<Light*>(d)) {
				// Arkadaþýnýn metodu: connect()
				l->connect();
			}
		}

		// --- ZINCIRI DEVAM ETTIR (Polis Ýçin) ---
		if (nextHandler) {
			nextHandler->handleRequest(event);
		}

	}
	else {
		BaseHandler::handleRequest(event);
	}
}