#ifndef LIGHT_ON_HANDLER_H
#define LIGHT_ON_HANDLER_H
#include "BaseHandler.h"
#include "../include/device_hierarchy/Device.h"
#include <vector>

class LightOnHandler : public BaseHandler {
public:
	LightOnHandler(const std::vector<Device*>& devices);
	void handleRequest(SecurityEvent event) override;
private:
	const std::vector<Device*>& allDevices_;
};
#endif