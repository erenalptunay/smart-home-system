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
int Camera::cameraId = 0;
int Light::lightId = 0;
// Alarm uses Device::idCounter, so no separate definition needed.

int main() {
	std::cout << "===== PROJE BASLATILIYOR =====" << std::endl;

	std::vector<Device*> devices; // Cihaz listesi

	
	Camera* cam = new Camera("Ana Kapi Kamerasi");
	devices.push_back(cam); // Kamerayı listeye ekle

	for (int i = 1; i <= 10; i++) {
		string lightName = "Light " + to_string(i);
		Light* l = new Light(lightName);

		// 6. Işık Bozuk Olmalı (Kapalı Kalması İçin)
		if (i == 6) {
			
			l->setBroken("Lamba kirilmis olabilir..."); // Işığı arızalı yap
		}

		devices.push_back(l);
	}

	// sistemini kuruyoruz
	SecuritySystem* system = new SecuritySystem(devices);

	
	cam->attach(system); // Kamerayı SecuritySystem'e bağlıyoruz

	std::cout << "\n[TEST] Hareket tetikleniyor..." << std::endl;
	cam->simulateMotionDetection(); // Hareket algılamayı simüle et . zinci başlatılır.

	// Temizlik
	delete system;
	for (auto d : devices) delete d;  //program bitince cihazları sil.

	return 0;
}