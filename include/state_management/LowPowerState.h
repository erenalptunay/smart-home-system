#ifndef LOW_POWER_STATE_H
#define LOW_POWER_STATE_H

#include "State.h"
#include "DeviceAdjustment.h"
#include <iostream>

class LowPowerState : public State
{
public:
    void enter(SystemStateManager*, DeviceAdjustment* dc)
    {
        std::cout << "\n[STATE TRANSITION] State changed to Low Power\n";
        std::cout << "-------------------------------------------\n";
        std::cout << "• CPU frequency reduced\n";
        std::cout << "• Display brightness lowered to 40%\n";
        std::cout << "• Background processes limited\n";
        std::cout << "• Non-essential devices set to idle\n";
        std::cout << "• Energy consumption significantly reduced\n";
        std::cout << "-------------------------------------------\n";
        std::cout << "System is optimized for energy efficiency.\n\n";
      
        dc->setLight(false);
        dc->setTV(false);
        dc->setMusic(true);

        dc->deviceStatus();
    
    }

    std::string getName() const override
    {
        return "Low Power";
    }
};

#endif
