#ifndef HIGH_PERFORMANCE_STATE_H
#define HIGH_PERFORMANCE_STATE_H

#include "State.h"
#include <iostream>

class HighPerformanceState : public State
{
public:
    void enter(SystemStateManager*)
    {
        std::cout << "\n[STATE TRANSITION] HIGH PERFORMANCE MODE ACTIVATED\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "• CPU performance profile set to MAXIMUM\n";
        std::cout << "• Display brightness adjusted to 100%\n";
        std::cout << "• Power-saving features DISABLED\n";
        std::cout << "• Device response latency minimized\n";
        std::cout << "• Energy consumption increased\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "System is now running at peak performance.\n\n";
    }

    std::string getName() const
    {
        return "High Performance";
    }
};

#endif
