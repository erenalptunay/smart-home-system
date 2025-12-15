#include <iostream>
#include <vector>
#include "../include/security_system/SecuritySystem.h"
#include "../include/device_hierarchy/Camera.h"
#include "../include/device_hierarchy/Light.h"
#include "../include/device_hierarchy/Alarm.h"


// bu değişkenleri burada canlandırıyoruz.
int Device::idCounter = 1; 
// Alarm instance Alarm.h içinde inline değilse burayı aç:
// Alarm* Alarm::instance = nullptr;
int Camera::cameraId = 1;
int Light::lightId = 1;
// Alarm uses Device::idCounter, so no separate definition needed.

int main() {
	std::cout << "===== PROJE BASLATILIYOR =====" << std::endl;

	std::vector<Device*> devices; // Cihaz listesi

	
	Camera* cam = new Camera("Ana Kapi Kamerasi");
	devices.push_back(cam); // Kamerayı listeye ekle

	devices.push_back(new Light("Salon Isigi")); // Işığı listeye ekle

	// sistemini kuruyoruz
	SecuritySystem* system = new SecuritySystem(devices);

	
	cam->attach(system); // Kamerayı SecuritySystem'e bağlıyoruz

	
	cam->simulateMotionDetection(); // Hareket algılamayı simüle et . zinci başlatılır.

	// Temizlik
	delete system;
	for (auto d : devices) delete d;  //program bitince cihazları sil.

	return 0;
}