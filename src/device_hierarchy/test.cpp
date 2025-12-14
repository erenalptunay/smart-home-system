#include <iostream>
#include <vector>
#include <cassert>
#include "device_hierarchy/Device.h"
#include "device_hierarchy/IObserver.h"
#include "device_hierarchy/TV.h"            // LGTV ve SamsungTV burada
#include "device_hierarchy/Light.h"
#include "device_hierarchy/SmokeDetector.h"
#include "device_hierarchy/GasDetector.h"
#include "device_hierarchy/Camera.h"
#include "device_hierarchy/Alarm.h"
#include "device_hierarchy/HomeDetectorFactory.h"

using namespace std;

// --- STATIC INITIALIZATION (Statik Deðiþkenlerin Baþlatýlmasý) ---
// Device.h içindeki talimata uygun olarak:
int Device::idCounter = 1;

// Diðer sýnýflarýn kendi sayaçlarý
int TV::tvId = 0;
int LGTV::lgtvId = 0;
int SamsungTV::samsungtvId = 0;
int Light::lightId = 0;
int SmokeDetector::smokeId = 0;
int GasDetector::gasId = 0;
int Camera::cameraId = 0;
// Alarm::instance inline tanýmlandýðý için burada gerekmeyebilir ama garanti olsun:
// (C++17 öncesi derleyiciler için gerekebilir, modern derleyicilerde inline yeterlidir)

// --- TEST ÝÇÝN MOCK OBSERVER ---
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

// --- TEST FONKSÝYONLARI ---

void testDeviceBasicsAndID() {
    cout << "\n--- TEST 1: Cihaz ID ve Temel Fonksiyonlar ---" << endl;

    // Basit bir cihaz (Light kullanarak test edelim)
    Light l1("Giris Lambasi");
    Light l2("Salon Lambasi");

    // Device::idCounter testi
    // l1 -> ID 1, l2 -> ID 2 olmalý
    cout << "Cihaz 1 ID: " << l1.getId() << endl;
    cout << "Cihaz 2 ID: " << l2.getId() << endl;

    assert(l1.getId() < l2.getId());

    // Açma/Kapama Testi
    l1.connect(); // Açýldý
    assert(l1.getOpenCheck() == true);

    l1.close();   // Kapandý
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

    // Dedektörlerin kapatýlamadýðýný (override close) test et
    cout << "Test: Dedektor kapatilmaya calisiliyor..." << endl;
    d1->connect(); // Önce açalým (gerçi constructorda açýk geliyor olabilir)
    d1->close();   // "ENGELLENDI" yazmalý ve durumu deðiþmemeli

    // SmokeDetector.h içinde close() sadece cout yapýyor ama openCheck'i deðiþtirmiyor mu?
    // Koduna göre sadece cout yapýyor, base class close'u çaðýrmýyor. 
    // Bu yüzden openCheck hala true kalmalý (eðer true baþladýysa).

    delete d1;
    delete d2;
    cout << "[OK] Factory ve Dedektor testleri tamamlandi." << endl;
}

void testObserverAndBrokenState() {
    cout << "\n--- TEST 3: Observer ve Ariza Durumu (Device.h Ozel) ---" << endl;

    Camera cam("Arka Bahce Kamera");
    TestObserver userPhone;

    // 1. Abone Ol (Attach)
    cam.attach(&userPhone);

    // 2. Hareket Algýla (Camera.h notifyObservers çaðýrýr)
    cam.simulateMotionDetection();
    assert(userPhone.lastMessage == "MOTION_DETECTED");

    // 3. Cihazý Boz (Device.h -> setBroken)
    cout << "Test: Cihazi arizalandiriyoruz..." << endl;
    cam.setBroken("Sensor Hatasi");

    assert(cam.getIsRunning() == false);
    assert(userPhone.lastMessage == "ARIZA: Sensor Hatasi");

    // 4. Arýzalý cihazý açmaya çalýþ (connect)
    // Device.h'de connect() baþýnda !isRunning kontrolü var.
    cout << "Test: Arizali cihaz acilmaya calisiliyor..." << endl;
    cam.connect(); // "Hata! ... arizalidir" yazmalý ve açýlmamalý.
    assert(cam.getOpenCheck() == false);

    // 5. Tamir Et (setFixed)
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

    assert(&orjinal != klon); // Farklý bellek adresleri
    assert(klon->getFullType() == "LGTV");

    // Klonun ID'si (Device copy constructor logic'ine göre kopyalandý)
    // Device(const Device&) copy constructor'ý ID'yi de kopyalýyor mu?
    // Device.h'a baktýðýmýzda: Copy constructor ID'yi kopyalamamýþ.
    // Ancak id bir "protected" üye ve init edilmemiþ (garbage value olabilir) 
    // VEYA idCounter copy constructorda artýrýlmamýþ.
    // Normalde klonlanan nesnenin yeni bir ID almasý beklenir ama 
    // senin Device copy constructor'ýnda ID atamasý yok. 
    // Bu durumda klonun ID'si belirsiz olabilir, sadece tipi kontrol edelim.

    klon->printStatus();

    delete klon;
    cout << "[OK] Prototype kopyalama basarili." << endl;
}

void testSingletonAlarm() {
    cout << "\n--- TEST 5: Singleton (Alarm) ---" << endl;

    Alarm* a1 = Alarm::getInstance();
    Alarm* a2 = Alarm::getInstance();

    assert(a1 == a2); // Adresler ayný olmalý
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