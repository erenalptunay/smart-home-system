#include <iostream>

#include "state_management/SystemStateManager.h"
#include "state_management/NormalState.h"
#include "state_management/HighPerformanceState.h"
#include "state_management/LowPowerState.h"
#include "state_management/SleepState.h"

int main()
{
    std::cout << "=============================\n";
    std::cout << "  STATE MANAGEMENT DEMO APP  \n";
    std::cout << "=============================\n\n";

    SystemStateManager stateManager;

    // Initial state
    stateManager.setState(new NormalState());

    std::cout << "\n>> Switching to High Performance...\n";
    stateManager.setState(new HighPerformanceState());

    std::cout << "\n>> Switching to Low Power...\n";
    stateManager.setState(new LowPowerState());

    std::cout << "\n>> Switching to Sleep...\n";
    stateManager.setState(new SleepState());

    std::cout << "\n>> Returning to Previous State...\n";
    stateManager.previousState();

    std::cout << "\n>> Current State Info:\n";
    stateManager.showState();

    std::cout << "\n=============================\n";
    std::cout << "       DEMO COMPLETED        \n";
    std::cout << "=============================\n";

    return 0;
}