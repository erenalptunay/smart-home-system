#pragma once
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "Device.h" 

class SoundSystem : public Device {
private:
    const static int mId = 1;
public:
    SoundSystem() : Device("Music Player") {
        this->id = mId;
        this->type = 'S';
    }

    // Prototip Deseni
    Device* clone() const override {
        return new SoundSystem(*this);
    }

    std::string getFullType() const override {
        return "MusicPlayer";
    }

    void printStatus() const override {
        Device::printStatus();
        cout << "[" << this->id << "] " << getFullType()
            << " | Guc: " << (openCheck ? "ACIK" : "KAPALI")
            << " | Durum: " << (isRunning ? "SAGLAM" : "ARIZALI") << endl;
    }
};

#endif
