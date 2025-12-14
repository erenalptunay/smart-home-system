#include "../include/security_system/SecuritySystem.h"
#include <iostream>

SecuritySystem::SecuritySystem(const std::vector<Device*>& devices) {  // cihazlarýn listesini alýr.
	alarmHandler = new AlarmHandler();
	lightHandler = new LightOnHandler(devices);
	policeHandler = new PoliceCallHandler();

	// Zinciri Kur: Alarm -> Iþýk -> Polis
	alarmHandler->setNext(lightHandler)->setNext(policeHandler);
}

SecuritySystem::~SecuritySystem() { // destructor method
	delete alarmHandler;
	delete lightHandler;
	delete policeHandler;
}

void SecuritySystem::update(const string& deviceName, const string& message) {   //"Sensörden gelen sinyali yakala ve 'Ben bu mesajý aldým' diye ekrana yaz.
	cout << "\n Mesaj Alindi: " << message << endl;

	// Þifre Kontrolü
	if (message == "MOTION_DETECTED") {
		cout << " Hareket onaylandi. Zincir baslatiliyor..." << endl;
		alarmHandler->handleRequest(SecurityEvent::MotionDetected);
	}
}