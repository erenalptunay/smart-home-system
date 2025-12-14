#ifndef CAMERA_H
#define CAMERA_H

#include "Device.h"

// Arkadaþýnýzýn Camera sýnýfý (Deðiþkenler ve yapý korundu)
class Camera : public Device {
private:
	string resolution;
	int fps;
	bool nightVision;

public:
	// Arkadaþýnýzýn Kurucusu (Aynen korundu)
	Camera(string n, string res = "1080p", int f = 24, bool nv = true)
		: Device(n), resolution(res), fps(f), nightVision(nv) {
	}

	// Arkadaþýnýzýn Clone Metodu (Aynen korundu)
	Device* clone() const override {
		return new Camera(*this);
	}

	// Arkadaþýnýzýn PrintStatus Metodu (Aynen korundu)
	void printStatus() const override {
		Device::printStatus();
		cout << "  -> Detaylar: Cozunurluk=" << resolution
			<< ", FPS=" << fps
			<< ", Gece Gorusu=" << (nightVision ? "Acik" : "Kapali") << endl;
	}

	// ---------------------------------------------------------
	// |         BÝZÝM EKLEDÝÐÝMÝZ KRÝTÝK BÖLÜM                |
	// ---------------------------------------------------------
	// Bu fonksiyonu sýnýfýn içine, public kýsmýna ekledik.
	void simulateMotionDetection() {
		// Cihaz bozuksa (isRunning false ise) iþlem yapma
		if (!getIsRunning()) {
			cout << name << " (ID: " << id << ") arizali, hareket algilama yapilamadi." << endl;
			return;
		}

		// Ekrana bilgi ver
		cout << "\n!!! " << name << " (ID: " << id << ") HAREKET ALGILADI !!!" << endl;

		// --- EN ÖNEMLÝ DÜZELTME BURASI ---
		// Arkadaþýnýzýn kodunda olmayan, SecuritySystem'in beklediði þifreyi gönderiyoruz:
		notifyObservers("MOTION_DETECTED");
	}
	// ---------------------------------------------------------

}; // Sýnýf bitiþi

#endif // CAMERA_H