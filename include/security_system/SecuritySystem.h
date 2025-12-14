#ifndef SECURITY_SYSTEM_H
#define SECURITY_SYSTEM_H

#include "../include/device_hierarchy/IObserver.h" // Arkadaþýnýn dosyasý
#include "../include/device_hierarchy/Device.h"
#include "AlarmHandler.h"
#include "LightOnHandler.h"
#include "PoliceCallHandler.h"
#include <vector>

// Senin sistemin artýk IObserver dilini konuþuyor
class SecuritySystem : public IObserver {
public:
	SecuritySystem(const std::vector<Device*>& devices);
	~SecuritySystem();

	// IObserver'dan gelen güncelleme metodu
	void update(const string& deviceName, const string& message) override;

private:
	AlarmHandler* alarmHandler;
	LightOnHandler* lightHandler;
	PoliceCallHandler* policeHandler;
};
#endif