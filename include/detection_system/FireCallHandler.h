#ifndef FIRECALLHANDLER_H
#define FIRECALLHANDLER_H

#include "EmergencyHandler.h"

// Handles the final emergency response (external call).
class FireCallHandler : public EmergencyHandler {
public:
    void handleRequest() override {
        cout << "[System] Calling Fire Station..." << endl;
        cout << "[System] Connection established. Emergency reported." << endl;
    }
};

#endif
