#ifndef ALARM_H
#define ALARM_H

#include "Device.h"

class Alarm : public Device {
private:
	static Alarm* instance;


	Alarm(string n) : Device(n) {
		cout << "Alarm Sistemi (" << n << ") baslatildi." << endl;
	}

public:
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

	// Prototype
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
