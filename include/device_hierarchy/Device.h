#ifndef DEVICE_H
#define DEVICE_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "IObserver.h"

using namespace std;

class Device {
protected:

	string name;
	bool openCheck; // Cihazın açık olup olmadığını kontrol eden değişken
	bool isRunning; // Cihazın çalışıp çalışmadığı (aktif / bozuk) kontrol eden değişken

	vector<IObserver*> observers; // Gözlemci listesi

public:
	Device(string n) : name(n), openCheck(false), isRunning(true) {}
	virtual ~Device(){
		observers.clear();
	}

	// Seçim yapma / Abone olma
	void attach(IObserver* obs) {
		observers.push_back(obs);
		cout << "[SISTEM] " << name << " icin yeni bildirim secildi." << endl;
	}


	// Seçimi kaldırma / İptal etme
	void detach(IObserver* obsToRemove) {
		for (auto it = observers.begin(); it != observers.end(); ++it) {
			if (*it == obsToRemove) {
				observers.erase(it);
				cout << "" << name << " icin bir bildirim secimi kaldirildi." << endl;
				break;
			}
		}
	}


	// Bildirim gönderme
	void notifyObservers(const string& message) {
		if (observers.empty()) {
			cout << "Cihaz arizalandi ama kullanici bildirim secmemis." << endl;
			return;
		}
		for (IObserver* obs : observers) {
			obs->update(name, message);
		}
	}


	string getName() const { 
		return name;
	}
	bool getOpenCheck() const {
		return openCheck;
	}
	bool getIsRunning() const {
		return isRunning;
	}

	// Cihaz açma işlemi
	virtual void connect() {
		if (!isRunning) {
			cout << " Hata!" << name << " arizalidir." << endl;
			return;
		}
		if (openCheck) {
			cout << name << " zaten hazir ve aktif durumdadir." << endl;
			return;
		}
		openCheck = 1;
		cout << name << " acildi." << endl;
	}

	// Cihaz kapatma işlemi
	virtual void close() {
		if (!openCheck) {
			cout << name << " zaten kapali." << endl;
			return;
		}
		
		openCheck = 0;
		cout << name << " kapatildi." << endl;
	}

	// Cihaz arızalı durumu

	void setBroken(string reason) {
		isRunning = 0;
		openCheck = 0;
		cout << "UYARI: " << name << " arizalandi! Sebep: " << reason << endl;
		notifyObservers("ARIZA: " + reason); // Kullanıcı seçtiyse bildirim gider
	}

	void setFixed() {
		isRunning = 1;
		cout << "BILGI: " << name << " tamir edildi." << endl;
		notifyObservers("TAMIR: Cihaz tekrar aktif.");
	}

	// Prototype tasarımı
	virtual Device* clone() const = 0;

	virtual void printStatus() const {
		cout << "Device: " << name << "\nGuc: " << (openCheck ? "Acik" : "Kapali") << "\nDurum: " << (isRunning ? "Sorunsuz" : "Arizali") << endl;
	}
};

#endif