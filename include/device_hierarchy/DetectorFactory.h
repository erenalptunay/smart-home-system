#pragma once
#ifndef DETECTORFACTORY_H
#define DETECTORFACTORY_H

#include "SmokeDetector.h"
#include "GasDetector.h"

// Soyut Fabrika (Abstract Factory) Arayüzü
class DetectorFactory {
public:
    // Bu metotlar, fabrika üzerinden ürün ailesini üretme kontratýdýr.
    virtual SmokeDetector* createSmokeDetector(string n) = 0;
    virtual GasDetector* createGasDetector(string n) = 0;

    virtual ~DetectorFactory() {}
};

#endif