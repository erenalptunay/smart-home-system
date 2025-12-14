#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <iostream>

class DeviceController
{
private:
    bool light;
    bool tv;
    bool music;
    bool camera;
    bool detector;

public:
    DeviceController()
        : light(false), tv(false), music(false),
        camera(true), detector(true) // always on
    {
    }

    void setLight(bool on) { light = on; }
    void setTV(bool on) { tv = on; }
    void setMusic(bool on) { music = on; }
    void setCamera(bool on) { camera = on; }
    void setDetector(bool on) { detector = on; }

    void deviceStatus() const
    {
        std::cout << "Device Status:\n";
        std::cout << " Light: " << (light ? "ON" : "OFF") << '\n';
        std::cout << " TV: " << (tv ? "ON" : "OFF") << '\n';
        std::cout << " Music: " << (music ? "ON" : "OFF") << '\n';
        std::cout << " Camera: " << (camera ? "ON" : "OFF") << '\n';
        std::cout << " Detector: " << (detector ? "ON" : "OFF") << '\n';
    }
};

#endif
