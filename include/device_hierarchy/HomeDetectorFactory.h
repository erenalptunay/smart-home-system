#pragma once
#ifndef HOMEDETECTORFACTORY_H
#define HOMEDETECTORFACTORY_H

#include "DetectorFactory.h"

// Somut Fabrika (Concrete Factory)
class HomeDetectorFactory : public DetectorFactory {
public:
    // SmokeDetector üretimi
    SmokeDetector* createSmokeDetector(string n) override {
        return new SmokeDetector(n);
    }

    // GasDetector üretimi
    GasDetector* createGasDetector(string n) override {
        return new GasDetector(n);
    }
};

#endif