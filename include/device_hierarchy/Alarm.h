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
    static Alarm* getInstance(string n = "Sistem Alarmı") {
        if (instance == nullptr) {
            instance = new Alarm(n);
        }
        return instance;
    }

    void close() override {
    }

    void connect() override {
        openCheck = true;
        cout << "\n>>> SIREN SESI: " << name << " CALIYOR! <<<" << endl;
    }

    Device* clone() const override {
        return nullptr;
    }

    void printStatus() const override {
        Device::printStatus();
    }
};

inline Alarm* Alarm::instance = nullptr;

#endif
