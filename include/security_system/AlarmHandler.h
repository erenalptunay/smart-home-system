#ifndef ALARM_HANDLER_H
#define ALARM_HANDLER_H

#include "BaseHandler.h"
#include "Alarm.h" // <<< C2061 ÇÖZÜMÜ: Alarm sýnýfýný dahil et

class AlarmHandler : public BaseHandler {
public:
    // Kurucu metot bildirimi: C2511'i çözer
    AlarmHandler(Alarm* alarm);

    void handleRequest(SecurityEvent event) override;

private:
    // <<< C2065 ÇÖZÜMÜ: alarm_ üye deðiþkenini tanýmla
    Alarm* alarm_;
    const int ALARM_DURATION_SECONDS = 5;
};
// HATA ÇÖZÜMÜ (C2238/C2143): Sýnýf tanýmýnýn sonunda noktalý virgül (;) OLMAZ!
// Sýnýfýn dýþýndaki include korumasýna dikkat edin.

#endif // ALARM_HANDLER_H