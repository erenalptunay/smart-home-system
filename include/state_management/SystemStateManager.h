#ifndef SYSTEM_STATE_MANAGER_H
#define SYSTEM_STATE_MANAGER_H

#include <vector>
#include "State.h"
#include "DeviceController.h"

class SystemStateManager
{
private:
    State* currentState;
    std::vector<State*> stateHistory;
    DeviceController controller;

public:
    SystemStateManager();
    ~SystemStateManager();

    void setState(State* state);
    void previousState();
    void showState() const;
    DeviceController* getController();

};

#endif
