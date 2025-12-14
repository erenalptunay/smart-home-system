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
    ObservableSmokeDetector(string n);

    void attach(IObserver* observer);

    void detach(IObserver* observer);

    void notify(const string& message);

    void detectSmoke();
};

#endif
