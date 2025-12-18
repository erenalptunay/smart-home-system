#include "../../include/detection_system/ObservableDetector.h"
#include <iostream>

using namespace std;

ObservableSmokeDetector::ObservableSmokeDetector(string n) : SmokeDetector(n) {}

void ObservableSmokeDetector::attach(IObserver* observer) {
    observers.push_back(observer);
}

void ObservableSmokeDetector::detach(IObserver* observer) {
    for (size_t i = 0; i < observers.size(); ++i) {
        if (observers[i] == observer) {
            observers.erase(observers.begin() + i);
            break;
        }
    }
}

void ObservableSmokeDetector::notify(const string& message) {
    for (auto observer : observers) {
        observer->update(getName(), message);
    }
}

void ObservableSmokeDetector::detectSmoke() {
    cout << "[Detector] Smoke detected by " << getName() << "!" << endl;
    notify("High smoke level detected");
}
