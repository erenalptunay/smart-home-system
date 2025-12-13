// BaseHandler.h içeriði
#ifndef BASE_HANDLER_H
#define BASE_HANDLER_H


#include "ISequenceHandler.h"
#include <iostream>

class BaseHandler : public ISequenceHandler {
public:
    // setNext metodunu uygular: sonraki iþleyiciyi ayarlar
    ISequenceHandler* setNext(ISequenceHandler* next) override {
        this->nextHandler = next;
        return next;
    }

    // handleRequest'in varsayýlan uygulamasý: 
    // Kendi iþini yapmazsa isteði zincirde ilerletir.
    void handleRequest(SecurityEvent event) override {
        // Eðer bir sonraki iþleyici varsa, isteði ona ilet.
        if (this->nextHandler) {
            this->nextHandler->handleRequest(event);
        }
        // Yoksa (yani zincirin sonuysa) burada sonlanýr.
    }
};

#endif // BASE_HANDLER_H