#include "SystemStateManager.h"
#include "State.h"
#include <iostream>

SystemStateManager::SystemStateManager()
    : currentState(0)
{
}

SystemStateManager::~SystemStateManager()
{
    for (size_t i = 0; i < stateHistory.size(); ++i)
    {
        delete stateHistory[i];
    }
    delete currentState;
}

void SystemStateManager::setState(State* state)
{
    if (currentState)
        stateHistory.push_back(currentState);

    currentState = state;
    currentState->enter(this);
}

void SystemStateManager::previousState()
{
    if (stateHistory.empty())
    {
        std::cout << "No previous state.\n";
        return;
    }

    delete currentState;
    currentState = stateHistory.back();
    stateHistory.pop_back();
    currentState->enter(this);
}

void SystemStateManager::showState() const
{
    if (currentState)
    {
        std::cout << "Current State: "
            << currentState->getName()
            << std::endl;
    }
}
