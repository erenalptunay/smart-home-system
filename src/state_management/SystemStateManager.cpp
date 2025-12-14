#include "state_management/SystemStateManager.h"
#include "state_management/State.h"
#include "state_management/NormalState.h"
#include <iostream>

SystemStateManager::SystemStateManager()
    : currentState(nullptr)
{
    setState(new NormalState());
}

SystemStateManager::~SystemStateManager()
{
    for (State* s : stateHistory)
      delete s;
    delete currentState;
}

void SystemStateManager::setState(State* state)
{
    if (currentState)
        stateHistory.push_back(currentState);

    currentState = state;
    currentState->enter(this, & controller);
}

void SystemStateManager::previousState()
{
    if (stateHistory.empty())
    {
        std::cout << "No previous state available.\n";
        return;
    }

    delete currentState;
    currentState = stateHistory.back();
    stateHistory.pop_back();
    currentState->enter(this, &controller);
}

void SystemStateManager::showState() const
{
    if (currentState)
    {
        std::cout << "Current State: "
            << currentState->getName()
            << std::endl;
        delete currentState;
    }
}
DeviceAdjustment* SystemStateManager::getController()
{
    return &controller;
}