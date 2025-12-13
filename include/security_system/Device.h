#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>

class Device {
public:
    virtual ~Device() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void printStatus() const = 0;
    virtual bool isActive() const { return true; }
};

// Light sýnýfý Device.h içinde tutuluyor
class Light : public Device {
public:
    Light(int id) : id_(id) {}

    // HATA ÇÖZÜMÜ: LightOnHandler.cpp'den eriþim için public metot eklenmeli
    int getId() const { return id_; }
    // Veya sadece id_ public yapýlabilirdi (ancak metot daha iyidir)

    void turnOn() override { std::cout << "Light " << id_ << " ON." << std::endl; }
    void turnOff() override { std::cout << "Light " << id_ << " OFF." << std::endl; }
    void printStatus() const override { std::cout << "[Light] Status: ID " << id_ << ", OK" << std::endl; }
private:
    int id_;
};

#endif // DEVICE_H
