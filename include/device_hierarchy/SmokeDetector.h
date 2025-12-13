#pragma once
#ifndef SMOKEDETECTOR_H
#define SMOKEDETECTOR_H

#include "Device.h" 

class SmokeDetector : public Device {
public:
    SmokeDetector(string n) : Device(n) {
        openCheck = true;
        isRunning = true; 
    }

    void close() override {
        cout << "ENGELLENDI: Duman Dedektoru kritiktir ve kapatilamaz." << endl;
    }

    Device* clone() const override {
        return new SmokeDetector(*this);
    }

    // ... (level deðiþkeni ve printStatus metotlarý buraya eklenecektir)
};

#endif