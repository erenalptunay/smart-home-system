#ifndef FIRECALLHANDLER_H
#define FIRECALLHANDLER_H

#include "EmergencyHandler.h"

// Handles the final emergency response (external call).
class FireCallHandler : public EmergencyHandler {
public:
    void handleRequest() override;
};

#endif
