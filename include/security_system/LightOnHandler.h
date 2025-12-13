// Dosya: LightOnHandler.h

#ifndef LIGHT_ON_HANDLER_H 
#define LIGHT_ON_HANDLER_H

#include "BaseHandler.h" // <<< Doðru include
#include "Device.h"
#include <vector>

class LightOnHandler : public BaseHandler {
public:
    LightOnHandler(const std::vector<Device*>& allDevices);
    void handleRequest(SecurityEvent event) override;

private:
    const std::vector<Device*>& allDevices_;
};

#endif // LIGHT_ON_HANDLER_H