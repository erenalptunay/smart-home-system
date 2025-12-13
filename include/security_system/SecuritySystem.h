#ifndef SECURITY_SYSTEM_H
#define SECURITY_SYSTEM_H

#include "SecurityObserver.h"
// Observer arayüzleri




#include "AlarmHandler.h"
#include "LightOnHandler.h"
#include "PoliceCallHandler.h"

class SecuritySystem : public SecurityObserver {
public:
    SecuritySystem(Alarm* alarm, const std::vector<Device*>& allDevices);
    ~SecuritySystem();

    // Observer: Kamera bildirim yaptýðýnda burasý çaðrýlýr.
    void onMotionDetected() override;

private:
    AlarmHandler* alarmHandler_;
    LightOnHandler* lightOnHandler_;
    PoliceCallHandler* policeCallHandler_;
};

#endif // SECURITY_SYSTEM_H