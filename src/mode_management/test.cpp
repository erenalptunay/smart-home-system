#include <iostream>
#include <vector>
#include <string>
#include "device_hierarchy/Device.h"
#include "device_hierarchy/Light.h"

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
    case CINEMA: return "CINEMA";
    default: return "UNKNOWN";
    }
}

class Observer {
public:
    virtual void update(ModeType mode) = 0;
    virtual ~Observer() {}
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

int main() {
    ModeManager& manager = ModeManager::instance();

    manager.setMode(NORMAL);
    std::cout << "Aktif Mod: " << modeToString(manager.getCurrentMode()) << std::endl;

    manager.setMode(EVENING);
    std::cout << "Aktif Mod: " << modeToString(manager.getCurrentMode()) << std::endl;

    manager.setMode(PARTY);
    std::cout << "Aktif Mod: " << modeToString(manager.getCurrentMode()) << std::endl;

    manager.setMode(CINEMA);
    std::cout << "Aktif Mod: " << modeToString(manager.getCurrentMode()) << std::endl;
}
