#ifndef NORMAL_STATE_H
#define NORMAL_STATE_H

#include "State.h"
#include "DeviceController.h"
#include <iostream>

class NormalState : public State
{
public:
    void enter(SystemStateManager*, DeviceController* dc) override
    {
        std::cout << "\n[STATE TRANSITION] State changed to Normal\n";
        std::cout << "----------------------------------------\n";
        std::cout << "• System performance balanced\n";
        std::cout << "• Display brightness set to optimal level\n";
        std::cout << "• Power consumption stabilized\n";
        std::cout << "• Devices operating in standard mode\n";
        std::cout << "----------------------------------------\n";
        std::cout << "System is running under normal conditions.\n\n";
       
        dc->setLight(true);
        dc->setTV(false);
        dc->setMusic(false);

        dc->printStatus();
    }

    std::string getName() const override
    {
        return "Normal";
    }
};

#endif
