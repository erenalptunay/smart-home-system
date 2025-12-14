#pragma once
#ifndef TV_H
#define TV_H

#include "Device.h"

class TV : public Device {
protected:
    string brand;
    string model;
    bool isSmart;
    static int tvId;

public:
    TV(string n, string b, string m, bool smart)
        : Device(n), brand(b), model(m), isSmart(smart) {
        this->type = 't';
    }

    void printStatus() const override {
        Device::printStatus();
        cout << "  -> TV Marka: " << brand
            << ", Model: " << model
            << ", Tip: " << (isSmart ? "Smart" : "Dumb") << endl;
    }

};
//LG ve Samgung için ayrý id yönetimi
class LGTV : public TV {
private:
	static int lgtvId; 
public:
    LGTV(string n)
        : TV(n, "LG", "OLED-C3", true) {
        lgtvId++;
		this->id = lgtvId;
    } // Varsayilan konfigürasyon
    string getFullType() const override {
        return brand + "TV";
	}
// PROTOTYPE PATTERN (Klonlama)
    Device* clone() const override {
        return new LGTV(*this);
    }
};

class SamsungTV : public TV {
private:
	static int samsungtvId;
public:
    SamsungTV(string n)
        : TV(n, "Samsung", "QLED-8K", true) {
        samsungtvId++;
		this->id = samsungtvId;
  
    } // Varsayilan konfigürasyon
    string getFullType() const override {
        return brand + "TV";
    }
    Device* clone() const override {
        return new SamsungTV(*this);
    }
};

#endif
