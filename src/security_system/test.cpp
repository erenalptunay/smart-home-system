#include <iostream>
#include <vector>
#include "../include/security_system/SecuritySystem.h"
#include "../include/device_hierarchy/Camera.h"
#include "../include/device_hierarchy/Light.h"
#include "../include/device_hierarchy/Alarm.h"


// bu deðiþkenleri burada canlandýrýyoruz.
int Device::idCounter = 1; 
// Alarm instance Alarm.h içinde inline deðilse burayý aç:
// Alarm* Alarm::instance = nullptr;

int main() {
	std::cout << "===== PROJE BASLATILIYOR =====" << std::endl;

	std::vector<Device*> devices; // Cihaz listesi

	
	Camera* cam = new Camera("Ana Kapi Kamerasi");
	devices.push_back(cam); // Kamerayý listeye ekle

	devices.push_back(new Light("Salon Isigi")); // Iþýðý listeye ekle

	// sistemini kuruyoruz
	SecuritySystem* system = new SecuritySystem(devices);

	
	cam->attach(system); // Kamerayý SecuritySystem'e baðlýyoruz

	
	cam->simulateMotionDetection(); // Hareket algýlamayý simüle et . zinci baþlatýlýr.

	// Temizlik
	delete system;
	for (auto d : devices) delete d;  //program bitince cihazlarý sil.

	return 0;
}