#pragma once
#ifndef GASDETECTOR_H
#define GASDETECTOR_H

#include "Device.h" 

class GasDetector : public Device {
private:
    int gasLevel;
    static int gasId;

public:
    GasDetector(string n) : Device(n), gasLevel(0) {
        openCheck = true;
        isRunning = true;
        gasId++; 
        this->id = gasId; //Gas Detector idleri
        this->type = 'g';
    }

    // Prototype Pattern (Klonlama)
    Device* clone() const override {
        return new GasDetector(*this);
    }

    string getFullType() const {
        return "Smoke & Gas Detector";
    }

    void close() override {
        cout << "ENGELLENDI: Gaz Dedektoru kritiktir ve kapatilamaz." << endl;
    }

    void updateLevel(int level) { gasLevel = level; }

    void printStatus() const override {
        Device::printStatus();
        cout << "  -> Gaz Seviyesi: " << gasLevel << endl;
    }
};

#endif
