#ifndef NORMAL_STATE_H
#define NORMAL_STATE_H

#include "State.h"
#include "DeviceAdjustment.h"
#include <iostream>

class NormalState : public State
{
public:
	void enter(SystemStateManager*, DeviceAdjustment* dc) override
	{
		std::cout << "\n[STATE TRANSITION] State changed to Normal" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "• System performance balanced" << std::endl;
		std::cout << "• Display brightness set to optimal level" << std::endl;
		std::cout << "• Power consumption stabilized" << std::endl;
		std::cout << "• Devices operating in standard mode" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "System is running under normal conditions." << std::endl << std::endl;

		dc->setLight(true);
		dc->setTV(false);
		dc->setMusic(false);

		dc->deviceStatus();
	}

	std::string getName() const override
	{
		return "Normal";
	}
};

#endif
