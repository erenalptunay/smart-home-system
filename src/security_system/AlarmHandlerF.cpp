#include "../include/security_system/AlarmHandlerF.h"
#include <iostream>  // Ekrana yazý yazmak için (cout)
#include <thread>   // Ýþlemciyi uyutmak/bekletmek için
#include <chrono>  // Zaman birimleri için (saniye, dakika vs.)

AlarmHandlerF::AlarmHandlerF() {
	alarmInstance_ = Alarm::getInstance();  // Singleton Alarm örneðini al ve buraya getirmek için kullanýlýr.
}

void AlarmHandlerF::handleRequest1(SecurityEvent event) {  // bu metod, gelen güvenlik olayýný iþler.harete algýla olayý (mesala camýn kýrýlmasý gibi)
	if (event == SecurityEvent::MotionDetected) {
		std::cout << "\n--- AlarmHandler Devrede ---" << std::endl;  //Ekrana "Ben baþladým" mesajý yazýyor.

		if (alarmInstance_) alarmInstance_->connect();

		// --- DEÐÝÞÝKLÝK BURADA: 3 yerine 5 yaptýk ---
		std::cout << "   -> Alarm 5 saniye boyunca caliyor..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));  // 5 saniye boyunca bekletir.

		if (alarmInstance_) alarmInstance_->close();  //5 saniye sonra alarmý sonrak adým için alarm.h daki close fonksiyonunu çaðýrýr. alarm kapatýlmaz sadece fonksiyonun adý bu þekilde. 

		if (nextHandler) {
			std::cout << "   ->  sira Isiklarý acmaya geldi..." << std::endl;  //alarmdan sonra ýþýklarýn açýlmasý için mesaj yazdýrýr.
			nextHandler->handleRequest1(event);
		}
	}
	else {
		BaseHandler::handleRequest1(event); //eger dosyayý bilmiyorsa basehandler a gönderir.
	}
}