#ifndef NORMAL_STATE_H
#define NORMAL_STATE_H

#include "State.h"
#include <iostream>

class NormalState : public State
{
public:
    void enter(SystemStateManager*)
    {
        std::cout << "\n[STATE TRANSITION] NORMAL MODE ACTIVATED\n";
        std::cout << "----------------------------------------\n";
        std::cout << "• System performance balanced\n";
        std::cout << "• Display brightness set to optimal level\n";
        std::cout << "• Power consumption stabilized\n";
        std::cout << "• Devices operating in standard mode\n";
        std::cout << "----------------------------------------\n";
        std::cout << "System is running under normal conditions.\n\n";
    }

    std::string getName() const
    {
        return "Normal";
    }
};

#endif
