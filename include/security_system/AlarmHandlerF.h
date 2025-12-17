#ifndef ALARM_HANDLERF_H
#define ALARM_HANDLERF_H
#include "BaseHandler.h"
#include "../include/device_hierarchy/Alarm.h"

class AlarmHandlerF : public BaseHandler {    //AlarmHandler sýnýfýný, BaseHandler sýnýfýndan türetiliyor.
public:
	AlarmHandlerF();
	void handleRequest1(SecurityEvent event) override;   // handleRequest metodunu override ediyoruz.
private:
	Alarm* alarmInstance_;  //Singleton deseni ile Alarm sýnýfýnýn tek bir örneðini tutmak için bir iþaretçi.  alarmInstance_ anahtarýný kullanarak alarmý çalýstýrýrým.
};
#endif