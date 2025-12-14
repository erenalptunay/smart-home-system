#ifndef ALARM_H
#define ALARM_H

#include "Device.h"

class Alarm : public Device {
private:
	static Alarm* instance;   // Singleton instance


	// Private constructor (Singleton)
	Alarm(string n) : Device(n) {
		cout << "Alarm Sistemi (" << n << ") baslatildi." << endl;
	}

public:
	// Singleton erişim fonksiyonu
	static Alarm* getInstance(string n) {

		if (instance == nullptr) {
			instance = new Alarm(n);
		}
		return instance;
	}


	void close() override {
		cout << "[ALARM] Alarm sistemi kapatiliyor..." << endl;
		Device::close();
	}

	// Prototype (Singleton olduğu için kopya yok)
	Device* clone() const override {
		return nullptr;
	}

	string getFullType() const override {
		return "Alarm";
	}

	// Alarm'a özel fonksiyon
	void activate() {
		if (openCheck) {
			cout << getFullType() << " aktif edildi ve izleniyor." << endl;
		}
		else {
			cout << getFullType() << " acik degil. Once cihazi acmaniz gerekir." << endl;
		}
	}
};

/* -------- static member definition -------- */
inline Alarm* Alarm::instance = nullptr;

#endif
