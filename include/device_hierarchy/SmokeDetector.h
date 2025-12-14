#pragma once
#ifndef SMOKEDETECTOR_H
#define SMOKEDETECTOR_H

#include "Device.h" 

class SmokeDetector : public Device {

private:
    static int smokeId;
public:
    SmokeDetector(string n) : Device(n) {
        openCheck = true;
        isRunning = true; 
        smokeId++;
        this->id = smokeId;
        this->type = 'd';
    }

    void close() override {
        cout << "ENGELLENDI: Duman Dedektoru kritiktir ve kapatilamaz." << endl;
    }

    Device* clone() const override {
        return new SmokeDetector(*this);
    }

    string getFullType() const {
        return "Smoke & Gas Detector";
    }
    void printStatus() const override {
        Device::printStatus();
    }
};

#endif
