#ifndef SLEEP_STATE_H
#define SLEEP_STATE_H

#include "State.h"
#include "DeviceAdjustment.h"
#include <iostream>

class SleepState : public State
{
public:
    void enter(SystemStateManager*, DeviceAdjustment* dc)
    {
        std::cout << "\n[STATE TRANSITION] State changed to Sleep\n";
        std::cout << "--------------------------------------\n";
        std::cout << "• Display turned OFF\n";
        std::cout << "• Lights dimmed to minimum\n";
        std::cout << "• Non-critical devices powered down\n";
        std::cout << "• Network activity minimized\n";
        std::cout << "• Energy consumption at lowest level\n";
        std::cout << "--------------------------------------\n";
        std::cout << "System is now in sleep mode.\n\n";
       
        dc->setLight(false);
        dc->setTV(false);
        dc->setMusic(false);

        dc->deviceStatus();
    }

    std::string getName() const override
    {
        return "Sleep";
    }
};

#endif
