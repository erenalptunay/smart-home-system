#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Device.h"


class Camera : public Device {
private:
    string resolution;
    int fps;
    bool nightVision;

public:
    Camera(string n, string res = "1080p", int f = 24, bool nv = true)
        : Device(n), resolution(res), fps(f), nightVision(nv) {
    }

    Device* clone() const override {
        return new Camera(*this);
    }

    void printStatus() const override {
        Device::printStatus();
        cout << "  -> Detaylar: Cozunurluk=" << resolution
            << ", FPS=" << fps
            << ", Gece Gorusu=" << (nightVision ? "Acik" : "Kapali") << endl;
    }
};

#endif