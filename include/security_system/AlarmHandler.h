#ifndef ALARM_HANDLER_H
#define ALARM_HANDLER_H
#include "BaseHandler.h"
#include "../include/device_hierarchy/Alarm.h"

class AlarmHandler : public BaseHandler {
public:
	AlarmHandler();
	void handleRequest(SecurityEvent event) override;
private:
	Alarm* alarmInstance_;
};
#endif