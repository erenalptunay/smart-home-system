#include <iostream>
#include <vector>
#include <string>
#include "device_hierarchy/Device.h"

enum ModeType {
    NORMAL,
    EVENING,
    PARTY,
    CINEMA
};

std::string modeToString(ModeType mode) {
    switch (mode) {
    case NORMAL: return "NORMAL";
    case EVENING: return "EVENING";
    case PARTY: return "PARTY";
    default: return "UNKNOWN";
    }
}
class Observer {
public:
    virtual void update(ModeType mode) = 0;
    virtual ~Observer() {}
};

class DeviceController : public Observer {
private:
    bool light;
    bool tv;
    bool music;
    bool camera;
    bool detector;

public:
    DeviceController()
        : light(false), tv(false), music(false),
        camera(true), detector(true) {
    }

    void setLight(bool on) { light = on; }
    void setTV(bool on) { tv = on; }
    void setMusic(bool on) { music = on; }
    void setCamera(bool on) { camera = on; }
    void setDetector(bool on) { detector = on; }

    // Observer pattern
    void update(ModeType mode) override {
        switch (mode) {
        case NORMAL:
            setLight(true);
            setTV(false);
            setMusic(false);
            break;

        case EVENING:
            setLight(false);
            setTV(false);
            setMusic(false);
            break;

        case PARTY:
            setLight(true);
            setTV(false);
            setMusic(true);
            break;

        case CINEMA:
            setLight(false);
            setTV(true);
            setMusic(false);
            break;
        }

        // Her zaman açık
        setCamera(true);
        setDetector(true);
    }
};

class ModeManager {
private:
    ModeType currentMode;
    std::vector<Observer*> observers;

    ModeManager() : currentMode(NORMAL) {}

public:
    static ModeManager& instance() {
        static ModeManager instance;
        return instance;
    }

    void attach(Observer* obs) {
        observers.push_back(obs);
    }

    void setMode(ModeType newMode) {
        currentMode = newMode;
        notify();
    }

    ModeType getCurrentMode() const {
        return currentMode;
    }

private:
    void notify() {
        for (Observer* obs : observers) {
            obs->update(currentMode);
        }
    }
};

