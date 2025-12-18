#ifndef POLICE_CALL_HANDLER_H
#define POLICE_CALL_HANDLER_H
#include "BaseHandler.h"

class PoliceCallHandler : public BaseHandler {
public:
	void handleRequest1(SecurityEvent event) override; // gelen olaya bakarak polisi arar.
};
#endif