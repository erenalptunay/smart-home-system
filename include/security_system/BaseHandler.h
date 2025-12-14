#ifndef BASE_HANDLER_H
#define BASE_HANDLER_H
#include "SecurityEvent.h"

class BaseHandler {
public:
	virtual ~BaseHandler() = default;

	virtual BaseHandler* setNext(BaseHandler* next) {
		this->nextHandler = next;
		return next;
	}

	virtual void handleRequest(SecurityEvent event) {
		if (this->nextHandler) this->nextHandler->handleRequest(event);
	}
protected:
	BaseHandler* nextHandler = nullptr;
};
#endif