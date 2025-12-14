#include "../../include/detection_system/EmergencyHandler.h"

using namespace std;

EmergencyHandler::EmergencyHandler() : nextHandler(nullptr) {}

EmergencyHandler::~EmergencyHandler() {
    if (nextHandler) delete nextHandler;
}

void EmergencyHandler::setNext(EmergencyHandler* handler) {
    nextHandler = handler;
}

void EmergencyHandler::handleRequest() {
    if (nextHandler) {
        nextHandler->handleRequest();
    }
}

void EmergencyHandler::update(const string& deviceName, const string& message) {
    cout << "ALARM TRIGGERED! Source: " << deviceName << " - Message: " << message << endl;
    handleRequest();
}
