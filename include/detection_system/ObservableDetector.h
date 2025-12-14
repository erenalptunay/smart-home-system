#ifndef OBSERVABLEDETECTOR_H
#define OBSERVABLEDETECTOR_H

#include "../device_hierarchy/SmokeDetector.h"
#include "../device_hierarchy/IObserver.h"
#include <vector>
#include <algorithm>

// Extends SmokeDetector to support Observer pattern without modifying base class.
class ObservableSmokeDetector : public SmokeDetector {
private:
    vector<IObserver*> observers;

public:
    ObservableSmokeDetector(string n) : SmokeDetector(n) {}

    void attach(IObserver* observer) {
        observers.push_back(observer);
    }

    void detach(IObserver* observer) {
        for (size_t i = 0; i < observers.size(); ++i) {
            if (observers[i] == observer) {
                observers.erase(observers.begin() + i);
                break;
            }
        }
    }

    void notify(const string& message) {
        for (auto observer : observers) {
            observer->update(getName(), message);
        }
    }

    void detectSmoke() {
        cout << "[Detector] Smoke detected by " << getName() << "!" << endl;
        notify("High smoke level detected");
    }
};

#endif
