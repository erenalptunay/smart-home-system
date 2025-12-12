#ifndef ALARM_H
#define ALARM_H

#include "Device.h"
#include <iostream>

using namespace std;

class Alarm : public Device {
private:
    static Alarm* instance;   // Singleton instance

    // Private constructor (Singleton)
    Alarm(string n) : Device(n) {
        cout << "Alarm Sistemi (" << n << ") baslatildi." << endl;
    }

public:
    // Singleton eriþim fonksiyonu
    static Alarm* getInstance(string n) {
        if (instance == nullptr) {
            instance = new Alarm(n);
        }
        return instance;
    }

    // Device'tan override edilen close
    void close() override {
        cout << "[ALARM] Alarm sistemi kapatiliyor..." << endl;
        Device::close();
    }

    // Prototype (Singleton olduðu için kopya yok)
    Device* clone() const override {
        return nullptr;
    }

    // Alarm'a özel fonksiyon
    void activate() {
        if (openCheck) {
            cout << "Alarm aktif edildi ve izleniyor." << endl;
        }
        else {
            cout << "Once cihazi acmaniz gerekir." << endl;
        }
    }
};

/* -------- static member definition -------- */
inline Alarm* Alarm::instance = nullptr;

#endif
