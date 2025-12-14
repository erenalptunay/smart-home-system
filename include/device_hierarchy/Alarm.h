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
	static Alarm* getInstance(string n = "Sistem Alarmi") {
		if (instance == nullptr) {
			instance = new Alarm(n);
		}
		return instance;
	}
	void connect() override {
		openCheck = true;
		cout << "\n >>> SIREN SESI: " << name << " CALIYOR ! <<<" << endl;
	}

	void close() override {} // Alarm zaten kapatılamaz

	Device* clone() const override {
		return nullptr;
	}

	string getFullType() const override {
		return "Alarm";
	}
};

/* -------- static member definition -------- */
inline Alarm* Alarm::instance = nullptr;

#endif
