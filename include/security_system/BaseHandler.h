#ifndef BASE_HANDLER_H
#define BASE_HANDLER_H
#include "SecurityEvent.h"

class BaseHandler {
public:
	virtual ~BaseHandler() = default;  //Bunu yapmazsan, AlarmHandler silinirken hafýzada çöp býrakabilir. Bu satýr, temizliðin doðru sýrayla yapýlmasýný garanti eder.

	virtual BaseHandler* setNext(BaseHandler* next) {   //Alarm -> Iþýk -> Kamera sistemin dizilebilmesinin saðlandýðý yer burasýdýr.
		this->nextHandler = next;  //Sonraki iþleyiciyi ayarlar.
		return next;  //Zincirleme çaðrýlar için sonraki iþleyiciyi döndürür.  
	}

	virtual void handleRequest1(SecurityEvent event) {  //virtual metod, alt sýnýflar tarafýndan override edilebilir.
		if (this->nextHandler) this->nextHandler->handleRequest1(event);  //Eðer sonraki iþleyici varsa, isteði ona iletir.Eðer kimse yoksa, istek burada ölür.
	}
protected:
	BaseHandler* nextHandler = nullptr;  //Sonraki iþleyiciyi tutan iþaretçi.
};
#endif