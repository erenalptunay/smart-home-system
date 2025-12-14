#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Device.h"


class Camera : public Device {
private:
    string resolution;
    int fps;
    bool nightVision;
    static int cameraId; //ID'yi doðru yönetmek için

public:
    Camera(string n, string res = "1080p", int f = 24, bool nv = true)
		: Device(n), resolution(res), fps(f), nightVision(nv) {
        cameraId++;
		this->id = cameraId;//ID'yi doðru yönetmek için
        this->type = 'c';
    }
    string getFullType() const {
        return "Camera";
    }
    Device* clone() const override {
        return new Camera(*this);
    }

    void printStatus() const override {
        Device::printStatus();
        cout <<  "  -> Detaylar: Cozunurluk=" << resolution
            << ", FPS=" << fps
            << ", Gece Gorusu=" << (nightVision ? "Acik" : "Kapali") << endl;
    }

	void simulateMotionDetection() {
	if (!getIsRunning()) {
		cout << name << " (ID: " << id << ") arizali, hareket algilama yapilamadi." << endl;
		return;
	}

	cout << "\n!!! " << name << " (ID: " << id << ") HAREKET ALGILADI !!!" << endl;
	notifyObservers("MOTION_DETECTED");
}
};


#endif
