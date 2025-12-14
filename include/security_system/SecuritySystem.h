#ifndef SECURITY_SYSTEM_H
#define SECURITY_SYSTEM_H

#include "../include/device_hierarchy/IObserver.h" 
#include "../include/device_hierarchy/Device.h"
#include "AlarmHandler.h"
#include "LightOnHandler.h"
#include "PoliceCallHandler.h"
#include <vector>


class SecuritySystem : public IObserver { // SecuritySystem, IObserver arayüzünden türetilir. hareket algýlandýðýnda bildirim alýr.
public:
	SecuritySystem(const std::vector<Device*>& devices); // cihazlarýn listesini alýr.
	~SecuritySystem();  // destructor method

	// IObserver'dan gelen güncelleme metodu
	void update(const string& deviceName, const string& message) override; // cihazdan gelen bildirimleri alýr. 
	//nasýl çalýsýr
	//1.Evdeki hareket sensörü(Device) bir hareket algýlar.
	//2.Bu hareket algýlama olayýný SecuritySystem'e bildirir (notifyObservers ile).
	//3.SecuritySystem, bu bildirimi alýr update metodu ile çalýstýrýr
	//4.update metodu, hareket algýlama olayýný (SecurityEvent::MotionDetected) AlarmHandler'a iletir.
	//5.AlarmHandler, bu olaya göre alarmý çaldýrýr.

private:
	AlarmHandler* alarmHandler;
	LightOnHandler* lightHandler;
	PoliceCallHandler* policeHandler;
};
#endif