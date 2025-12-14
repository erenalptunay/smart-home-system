#ifndef HIGH_PERFORMANCE_STATE_H
#define HIGH_PERFORMANCE_STATE_H

#include "State.h"
#include <iostream>

class HighPerformanceState : public State
{
public:
    void enter(SystemStateManager* , DeviceController* dc) override
    {
    {
        std::cout << "\n[STATE TRANSITION] State changed to High Performance\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "• CPU performance profile set to MAXIMUM\n";
        std::cout << "• Display brightness adjusted to 100%\n";
        std::cout << "• Power-saving features DISABLED\n";
        std::cout << "• Device response latency minimized\n";
        std::cout << "• Energy consumption increased\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "System is now running at peak performance.\n\n";
        
       
        dc->setLight(true);
        dc->setTV(true);
        dc->setMusic(true);

        dc->printStatus();
    }

    std::string getName() const override
    {
        return "High Performance";
    }
};

#endif
