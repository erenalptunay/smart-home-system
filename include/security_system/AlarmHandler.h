#ifndef ALARM_HANDLER_H
#define ALARM_HANDLER_H
#include "BaseHandler.h"
#include "../include/device_hierarchy/Alarm.h"

class AlarmHandler : public BaseHandler {    //AlarmHandler sýnýfýný, BaseHandler sýnýfýndan türetiliyor.
public:
	AlarmHandler();
	void handleRequest(SecurityEvent event) override;   // handleRequest metodunu override ediyoruz.
private:
	Alarm* alarmInstance_;  //Singleton deseni ile Alarm sýnýfýnýn tek bir örneðini tutmak için bir iþaretçi.  alarmInstance_ anahtarýný kullanarak alarmý çalýstýrýrým.
};
#endif