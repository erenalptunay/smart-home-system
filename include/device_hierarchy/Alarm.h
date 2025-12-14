#ifndef ALARM_H
#define ALARM_H

#include "Device.h"
#include <iostream>

using namespace std;

class Alarm : public Device {
private:
	static Alarm* instance;   // Singleton instance

	
	Alarm(string n) : Device(n) {
		cout << "Alarm Sistemi (" << n << ") baslatildi." << endl;
	}

public:

	//  DEÐÝÞÝKLÝK 1: Varsayýlan Parametre Eklendi            
	
	// Eskisi: static Alarm* getInstance(string n)
	// Yenisi: (string n = "Sistem Alarmý") yaptýk ki boþ çaðýrabilesin.
	static Alarm* getInstance(string n = "Sistem Alarmý") {
		if (instance == nullptr) {
			instance = new Alarm(n);
		}
		return instance;
	}

	// DEÐÝÞÝKLÝK 2: Kapatma Korumasý           

	// Arkadaþýn Device::close() çaðýrýyordu, onu sildik.
	// Çünkü alarmýn güvenlik gereði kapanmamasý lazým.
	void close() override {
	//	cout << "[ALARM] UYARI: Guvenlik protokolu geregi alarm kapatilamaz." << endl;
		
	}

	
	//  EKLEME 1: connect() Metodu                            
	
	// Senin AlarmHandler.cpp dosyan "alarm->connect()" komutunu 
	// kullandýðý için bu fonksiyonu eklemek ZORUNDAYIZ.
	void connect() override {
		openCheck = true;
		cout << "\n>>> SIREN SESI: " << name << " CALIYOR! <<<" << endl;
	}



	
	Device* clone() const override {
		return nullptr;
	}



	// Gerekirse printStatus (Device'tan miras alýr, sorun yok)
	void printStatus() const override {
		Device::printStatus();
	}
};

/* -------- static member definition -------- */
inline Alarm* Alarm::instance = nullptr;

#endif