#ifndef LIGHT_ON_H
#define LIGHT_ON_H
#include "BaseHandler.h"
#include "../include/device_hierarchy/Device.h"
#include <vector>  //burada tek bir deðiþken deðil, cihazlarýn listesini tutmamýz gerekebilir diye kullanýyoruz.

class LightOn : public BaseHandler {  //olay hýrsýz girdiðinde lambalarý yakmak için hangi lambalarý yakacaðýný bilmek için bu sýnýfý kullanýyoruz.
public:
	LightOn(const std::vector<Device*>& devices);  //evdeki bütün cihazlarýn listesini (devices) vermen lazým. Yoksa hangi lambayý yakacaðýný bilemez.
	void handleRequest1(SecurityEvent event) override;
private:
	const std::vector<Device*>& allDevices_;  //Tüm cihazlarýn referansýný tutan bir iþaretçi.& Bu, bilgisayarý yormamak için çok önemlidir. Listenin fotokopisini çekmek yerine aslýna bakýyoruz)
};
#endif