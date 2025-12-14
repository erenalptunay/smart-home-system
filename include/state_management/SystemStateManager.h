#ifndef SYSTEM_STATE_MANAGER_H
#define SYSTEM_STATE_MANAGER_H

#include <vector>
#include "State.h"
#include "DeviceAdjustment.h"

class SystemStateManager
{
private:
    State* currentState;
    std::vector<State*> stateHistory;
    DeviceAdjustment controller;

public:
    SystemStateManager();
    ~SystemStateManager();

    void setState(State* state);
    void previousState();
    void showState() const;
    DeviceAdjustment* getController();

};

#endif
