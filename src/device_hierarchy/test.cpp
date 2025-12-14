#include <iostream>
#include <vector>
#include <cassert>
#include "device_hierarchy/Device.h"
#include "device_hierarchy/IObserver.h"
#include "device_hierarchy/TV.h"         
#include "device_hierarchy/Light.h"
#include "device_hierarchy/SmokeDetector.h"
#include "device_hierarchy/GasDetector.h"
#include "device_hierarchy/Camera.h"
#include "device_hierarchy/Alarm.h"
#include "device_hierarchy/HomeDetectorFactory.h"

using namespace std;

// --- STATIC INITIALIZATION (Statik Değişkenlerin Başlatılması) ---
int Device::idCounter = 1;

int TV::tvId = 0;
int LGTV::lgtvId = 0;
int SamsungTV::samsungtvId = 0;
int Light::lightId = 0;
int SmokeDetector::smokeId = 0;
int GasDetector::gasId = 0;
int Camera::cameraId = 0;


// --- TEST İÇİN MOCK OBSERVER ---
class TestObserver : public IObserver {
public:
    string lastMessage;
    string lastDevice;

    void update(const string& deviceName, const string& message) override {
        lastDevice = deviceName;
        lastMessage = message;
        cout << "\n[TEST OBSERVER] Gelen Bildirim -> " << deviceName << ": " << message << endl;
    }
};

// --- TEST FONKSİYONLARI ---

void testDeviceBasicsAndID() {
    cout << "\n--- TEST 1: Cihaz ID ve Temel Fonksiyonlar ---" << endl;

    Light l1("Giris Lambasi");
    Light l2("Salon Lambasi");

    cout << "Cihaz 1 ID: " << l1.getId() << endl;
    cout << "Cihaz 2 ID: " << l2.getId() << endl;

    assert(l1.getId() < l2.getId());

    // Açma/Kapama Testi
    l1.connect(); 
    assert(l1.getOpenCheck() == true);

    l1.close(); 
    assert(l1.getOpenCheck() == false);

    cout << "[OK] ID artisi ve acma/kapama basarili." << endl;
}

void testFactoryAndSecurity() {
    cout << "\n--- TEST 2: Factory Pattern ve Dedektor Guvenligi ---" << endl;

    HomeDetectorFactory factory;

    // Fabrika üzerinden üretim
    Device* d1 = factory.createSmokeDetector("Mutfak Duman Dedektoru");
    Device* d2 = factory.createGasDetector("Kazan Dairesi Gaz");

    d1->printStatus();
    d2->printStatus();

    cout << "Test: Dedektor kapatilmaya calisiliyor..." << endl;
    d1->connect();
    d1->close(); 

    delete d1;
    delete d2;
    cout << "[OK] Factory ve Dedektor testleri tamamlandi." << endl;
}

void testObserverAndBrokenState() {
    cout << "\n--- TEST 3: Observer ve Ariza Durumu (Device.h Ozel) ---" << endl;

    Camera cam("Arka Bahce Kamera");
    TestObserver userPhone;

    cam.attach(&userPhone);

    cam.simulateMotionDetection();
    assert(userPhone.lastMessage == "MOTION_DETECTED");

    cout << "Test: Cihazi arizalandiriyoruz..." << endl;
    cam.setBroken("Sensor Hatasi");

    assert(cam.getIsRunning() == false);
    assert(userPhone.lastMessage == "ARIZA: Sensor Hatasi");

    cout << "Test: Arizali cihaz acilmaya calisiliyor..." << endl;
    cam.connect(); // "Hata! ... arizalidir" yazmalı ve açılmamalı.
    assert(cam.getOpenCheck() == false);

    cam.setFixed();
    assert(cam.getIsRunning() == true);
    assert(userPhone.lastMessage == "TAMIR: Cihaz tekrar aktif.");

    cout << "[OK] Observer, Ariza ve Tamir senaryolari basarili." << endl;
}

void testPrototypePattern() {
    cout << "\n--- TEST 4: Prototype (Clone) ---" << endl;

    LGTV orjinal("Salon TV");
    Device* klon = orjinal.clone();

    cout << "Orjinal Adres: " << &orjinal << endl;
    cout << "Klon Adres:    " << klon << endl;

    assert(&orjinal != klon); // Farklı bellek adresleri
    assert(klon->getFullType() == "LGTV");


    klon->printStatus();

    delete klon;
    cout << "[OK] Prototype kopyalama basarili." << endl;
}

void testSingletonAlarm() {
    cout << "\n--- TEST 5: Singleton (Alarm) ---" << endl;

    Alarm* a1 = Alarm::getInstance();
    Alarm* a2 = Alarm::getInstance();

    assert(a1 == a2);
    cout << "Alarm Singleton Adresi: " << a1 << endl;

    if (a1->clone() == nullptr) {
        cout << "[OK] Alarm kopyalanamadi (Dogru davranis)." << endl;
    }
    else {
        cout << "[HATA] Alarm kopyalandi!" << endl;
    }
}

// --- MAIN ---
int main() {
    cout << "============================================" << endl;
    cout << "   AKILLI EV SISTEMI - OTOMATIK TESTLER     " << endl;
    cout << "============================================" << endl;

    testDeviceBasicsAndID();
    testFactoryAndSecurity();
    testObserverAndBrokenState();
    testPrototypePattern();
    testSingletonAlarm();

    cout << "\n============================================" << endl;
    cout << "   TUM TESTLER BASARIYLA TAMAMLANDI         " << endl;
    cout << "============================================" << endl;

    return 0;

}
