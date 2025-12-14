#ifndef LOW_POWER_STATE_H
#define LOW_POWER_STATE_H

#include "State.h"
#include <iostream>

class LowPowerState : public State
{
public:
    void enter(SystemStateManager*)
    {
        std::cout << "\n[STATE TRANSITION] LOW POWER MODE ACTIVATED\n";
        std::cout << "-------------------------------------------\n";
        std::cout << "• CPU frequency reduced\n";
        std::cout << "• Display brightness lowered to 40%\n";
        std::cout << "• Background processes limited\n";
        std::cout << "• Non-essential devices set to idle\n";
        std::cout << "• Energy consumption significantly reduced\n";
        std::cout << "-------------------------------------------\n";
        std::cout << "System is optimized for energy efficiency.\n\n";
    }

    std::string getName() const
    {
        return "Low Power";
    }
};

#endif
