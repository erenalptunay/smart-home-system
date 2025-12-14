#ifndef EMERGENCYHANDLER_H
#define EMERGENCYHANDLER_H

#include <iostream>
#include <string>
#include "../device_hierarchy/IObserver.h"

using namespace std;

// Base handler for Chain of Responsibility pattern.
// Implements IObserver to trigger the chain on detection events.
class EmergencyHandler : public IObserver {
protected:
    EmergencyHandler* nextHandler;

public:
    EmergencyHandler() : nextHandler(nullptr) {}
    virtual ~EmergencyHandler() {
        if (nextHandler) delete nextHandler;
    }

    void setNext(EmergencyHandler* handler) {
        nextHandler = handler;
    }

    virtual void handleRequest() {
        if (nextHandler) {
            nextHandler->handleRequest();
        }
    }

    // Triggered by detector events. Starts the emergency sequence.
    void update(const string& deviceName, const string& message) override {
        cout << "ALARM TRIGGERED! Source: " << deviceName << " - Message: " << message << endl;
        handleRequest();
    }
};

#endif
