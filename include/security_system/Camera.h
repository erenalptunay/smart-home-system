#ifndef CAMERA_H
#define CAMERA_H

#include "Device.h" 
#include "SecurityObserver.h" // HATA ÇÖZÜMÜ: Observer arayüzü dahil edildi
#include <vector>
#include <iostream>

// Camera, hem bir cihazdýr hem de Observer Subject'idir.
class Camera : public Device, public SecuritySubject {
    // ... sýnýfýn geri kalaný önceki haliyle ayný ...
public:
    Camera(bool securityActive = true) : securitySystemActive_(securityActive) {
        std::cout << "[Camera] Initialized (Security Active: " << (securityActive ? "Yes" : "No") << ")." << std::endl;
    }

    // --- Device Metotlarý ---
    void turnOn() override { std::cout << "Camera ON." << std::endl; }
    void turnOff() override { std::cout << "Camera OFF." << std::endl; }
    void printStatus() const override {
        std::cout << "[Camera] Status: Active, Security: " << (securitySystemActive_ ? "ON" : "OFF") << std::endl;
    }
    bool isActive() const override { return true; }

    // --- SecuritySubject Metotlarý ---
    void attach(SecurityObserver* observer) override {
        observers_.push_back(observer);
    }

    void detach(SecurityObserver* observer) override { /* ... */ }

    void notifyObservers() override {
        for (SecurityObserver* observer : observers_) {
            observer->onMotionDetected();
        }
    }

    void simulateMotionDetection() {
        if (securitySystemActive_) {
            std::cout << "\n[CAMERA] Motion detected! (Security System Active)" << std::endl;
            notifyObservers();
        }
        else {
            std::cout << "\n[CAMERA] Motion detected, but Security System is INACTIVE. Ignoring." << std::endl;
        }
    }

private:
    std::vector<SecurityObserver*> observers_;
    bool securitySystemActive_;
};

#endif // CAMERA_H