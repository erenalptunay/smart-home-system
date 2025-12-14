#ifndef CHANGE_STATE_H
#define CHANGE_STATE_H

#include <iostream>
#include "Command.h"
#include "SystemStateManager.h"
#include "NormalState.h"
#include "HighPerformanceState.h"
#include "LowPowerState.h"
#include "SleepState.h"

template<typename T>
T getSafeInput(const std::string& message)
{
    T value;
    while (true)
    {
        std::cout << message;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input!\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

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
        std::cout << "----- Change State -----\n";
        std::cout << "(N) Normal\n";
        std::cout << "(H) High Performance\n";
        std::cout << "(L) Low Power\n";
        std::cout << "(S) Sleep\n";
        std::cout << "(P) Previous State\n";

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
