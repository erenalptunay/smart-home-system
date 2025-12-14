#include "../include/security_system/SecuritySystem.h"
#include <iostream>

SecuritySystem::SecuritySystem(const std::vector<Device*>& devices) {
	alarmHandler = new AlarmHandler();
	lightHandler = new LightOnHandler(devices);
	policeHandler = new PoliceCallHandler();

	// Zinciri Kur: Alarm -> Iþýk -> Polis
	alarmHandler->setNext(lightHandler)->setNext(policeHandler);
}

SecuritySystem::~SecuritySystem() {
	delete alarmHandler;
	delete lightHandler;
	delete policeHandler;
}

void SecuritySystem::update(const string& deviceName, const string& message) {
	cout << "\n[SISTEM] Mesaj Alindi: " << message << endl;

	// Þifre Kontrolü
	if (message == "MOTION_DETECTED") {
		cout << "[SISTEM] Hareket onaylandi. Zincir baslatiliyor..." << endl;
		alarmHandler->handleRequest(SecurityEvent::MotionDetected);
	}
}