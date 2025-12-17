#ifndef CHANGE_STATE_H
#define CHANGE_STATE_H

#include <iostream>
#include "command_pattern/CommandP.h"
#include "SystemStateManager.h"
#include "NormalState.h"
#include "HighPerformanceState.h"
#include "LowPowerState.h"
#include "SleepState.h"
#include "DeviceAdjustment.h"

class ChangeState : public Command
{
private:
    SystemStateManager* stateManager;
public:
    explicit ChangeState(SystemStateManager* sm)
        : stateManager(sm) {
    }

    void execute() override
    {
        std::cout << "----- Change State -----" << std::endl;
        std::cout << "(N) Normal " << std::endl;
        std::cout << "(H) High Performance " << std::endl;
        std::cout << "(L) Low Power " << std::endl;
        std::cout << "(S) Sleep " << std::endl;
        std::cout << "(P) Previous State " << std::endl;

        char choice = getSafeInput<char>("Select state: ");

        switch (choice)
        {
        case 'N':
        case 'n':
            stateManager->setState(new NormalState());
            break;

        case 'H':
        case 'h':
            stateManager->setState(new HighPerformanceState());
            break;

        case 'L':
        case 'l':
            stateManager->setState(new LowPowerState());
            break;

        case 'S':
        case 's':
            stateManager->setState(new SleepState());
            break;

        case 'P':
        case 'p':
            stateManager->previousState();
            break;

        default:
            std::cout << "Invalid state selection.\n";
        }
    }
};

#endif // CHANGE_STATE_H
