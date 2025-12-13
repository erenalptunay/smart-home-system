#ifndef SECURITY_OBSERVER_H // HATA ÇÖZÜMÜ: Benzersiz koruma
#define SECURITY_OBSERVER_H

class SecurityObserver {
public:
    virtual ~SecurityObserver() = default;
    virtual void onMotionDetected() = 0;
};

class SecuritySubject {
public:
    virtual ~SecuritySubject() = default;
    virtual void attach(SecurityObserver* observer) = 0;
    virtual void detach(SecurityObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};

#endif // SECURITY_OBSERVER_H