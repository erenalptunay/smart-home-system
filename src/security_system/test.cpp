#include <iostream>
#include <vector>
#include "../include/security_system/SecuritySystem.h"
#include "../include/device_hierarchy/Camera.h"
#include "../include/device_hierarchy/Light.h"
#include "../include/device_hierarchy/Alarm.h"

// --- EN ÖNEMLÝ KISIM ---
// Arkadaþýnýn dosyalarýna dokunamadýðýmýz için, 
// bu deðiþkenleri burada canlandýrýyoruz.
int Device::idCounter = 1;
// Alarm instance Alarm.h içinde inline deðilse burayý aç:
// Alarm* Alarm::instance = nullptr;

int main() {
	std::cout << "===== PROJE BASLATILIYOR =====" << std::endl;

	std::vector<Device*> devices;

	// Arkadaþýnýn sýnýflarýný kullanýyoruz
	Camera* cam = new Camera("Ana Kapi Kamerasi");
	devices.push_back(cam);

	devices.push_back(new Light("Salon Isigi"));

	// Senin sistemini kuruyoruz
	SecuritySystem* system = new SecuritySystem(devices);

	// Baðlantýyý yapýyoruz (Ýkisi de IObserver olduðu için çalýþýr)
	cam->attach(system);

	// Test
	cam->simulateMotionDetection();

	// Temizlik
	delete system;
	for (auto d : devices) delete d;

	return 0;
}