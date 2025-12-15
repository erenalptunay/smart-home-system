#include "../include/security_system/LightOnHandler.h"
#include "../include/device_hierarchy/Light.h" 
#include <iostream>
#include <thread>
#include <chrono>

LightOnHandler::LightOnHandler(const std::vector<Device*>& devices) : allDevices_(devices) {} // Constructor: Cihaz listesini al ve referans olarak sakla .erilen o devices listesini al, benim cebimdeki allDevices_ deðiþkenine hemen kopyala.

void LightOnHandler::handleRequest(SecurityEvent event) {
	if (event == SecurityEvent::MotionDetected) {
		std::cout << "\n--- LightOnHandler Devrede ---" << std::endl;

		// Gerçekçilik için bekleme
		std::this_thread::sleep_for(std::chrono::seconds(1));  //1 saniye bekle

		for (Device* d : allDevices_) {  // Tüm cihazlarý tek tek dolaþ 

			if (Light* l = dynamic_cast<Light*>(d)) { // Cihaz bir Light (Lamba) ise ozaman artýk onu acýp kapatabiliriz.

				l->connect();  // Lambayý açma iþlemi için connect metodunu çaðýr oraya bakar arýza olup olmadýðýný kontrol eder.açýk olup olmadýðýný kontrol et acýk deðilse açar.

			}
		}
		std::cout << "   -> Isiklar 5 saniye acik kaliyor..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		
		for (Device* d : allDevices_) {
			if (Light* l = dynamic_cast<Light*>(d)) { //dynamic_cast filtreleme yapar.
				l->close();
			}
		}

		//zincirdeki bir sonraki iþleyiciye geç
		if (nextHandler) {
			nextHandler->handleRequest(event);
		}

	}
	else {
		BaseHandler::handleRequest(event);
	}
}