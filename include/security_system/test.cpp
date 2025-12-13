#include "SecuritySystem.h" // Sizin ana modülünüz
#include "Camera.h"
#include "Alarm.h"
#include "Device.h" // Light ve Alarm'ýn türediði temel sýnýf


#include <iostream>
#include <vector>
#include <algorithm>

// Ana Sistem Simülasyonu (MySweetHome'un temel iþlevleri)
class SystemIntegrator {
public:
    SystemIntegrator() {
        // 1. Cihazlarý oluþtur

        // Alarm (LLR-14)
        Alarm* alarm = new Alarm();
        devices_.push_back(alarm);

        // Iþýklar (LLR-41 isActive testi için birini bozuk yapalým)
        // Light sýnýfýnýn Device.h'de tanýmlandýðýný varsayýyoruz.
        devices_.push_back(new Light(1)); // Iþýk 1
        devices_.push_back(new Light(2)); // Iþýk 2

        // Kamera (Observer Subject)
        Camera* camera = new Camera(true);
        devices_.push_back(camera);

        // 2. Sizin modülünüzü (SecuritySystem) kur. Cihaz listesini ve Alarm'ý baðýmlýlýk olarak ver.
        securityManager_ = new SecuritySystem(alarm, devices_);

        // 3. Kamera'yý sizin SecuritySystem'inize baðla (Observer Pattern)
        camera->attach(securityManager_);

        std::cout << "\n[SystemIntegrator] Initial Setup Complete." << std::endl;
    }

    ~SystemIntegrator() {
        // Bellek sýzýntýsýný önlemek için silme (REQ10)
        delete securityManager_;
        for (Device* device : devices_) {
            delete device;
        }
    }

    // Kamera'dan gelen olayý simüle et
    void triggerSecuritySequence() {
        std::cout << "\n\n=================================================" << std::endl;
        std::cout << "SCENARIO: Triggering Security Sequence via Camera" << std::endl;
        std::cout << "=================================================" << std::endl;

        // devices listesindeki Camera'yý bul ve hareket algýlamayý tetikle
        for (Device* device : devices_) {
            Camera* camera = dynamic_cast<Camera*>(device);
            if (camera) {
                camera->simulateMotionDetection();
                return;
            }
        }
    }

private:
    std::vector<Device*> devices_;
    SecuritySystem* securityManager_;
};

int main() {
    SystemIntegrator system;

    // Güvenlik zincirini test et
    system.triggerSecuritySequence();

    return 0; // Yýkýcýlar çaðrýlýr.
}