#pragma once
#ifndef TV_H
#define TV_H

#include "Device.h"

class TV : public Device {
protected:
    string brand;
    string model;
    bool isSmart;

public:
    TV(string n, string b, string m, bool smart)
        : Device(n), brand(b), model(m), isSmart(smart) {
    }


    void printStatus() const override {
        Device::printStatus();
        cout << "  -> TV Marka: " << brand
            << ", Model: " << model
            << ", Tip: " << (isSmart ? "Smart" : "Dumb") << endl;
    }

};

class LGTV : public TV {
public:
    LGTV(string n)
        : TV(n, "LG", "OLED-C3", true) {
    } // Varsayilan konfigürasyon

// PROTOTYPE PATTERN (Klonlama)
    Device* clone() const override {
        return new LGTV(*this);
    }
};

class SamsungTV : public TV {
public:
    SamsungTV(string n)
        : TV(n, "Samsung", "QLED-8K", true) {
    } // Varsayilan konfigürasyon

    Device* clone() const override {
        return new SamsungTV(*this);
    }
};

#endif
