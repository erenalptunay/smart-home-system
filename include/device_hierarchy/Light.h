#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include "Device.h"

class Light : public Device {
private:
    int brightness; 
    string color;   
    static int lightId; 
public:
    Light(string n, string c = "White", int b = 100)
		: Device(n), color(c), brightness(b) {	
	
        lightId++;     
		this->id = lightId; 
		this->type = 'l'; 
    }

    // Prototype Pattern 
    Device* clone() const {
        return new Light(*this);
    }
    string getFullType() const { 
        return "Light";
    }

    // Iþýða özel metotlar
    void setBrightness(int b) { brightness = b; }
    void setColor(string c) { color = c; }
 
    void printStatus() const {
        Device::printStatus();
        cout << " Renk= " << color << ", Parlaklik= %" << brightness << endl;
    }
};
class ChinaLamp : public Light {
private:
    static int cLightId;
public:
    ChinaLamp(string n)
        : Light(n) {
        cLightId++;
        this->id = cLightId;
    }
    string getFullType() const override {
        return "China Lamp";
    }

    // PROTOTYPE PATTERN (Klonlama)
    Device* clone() const override {
        return new ChinaLamp(*this);
    }
    void printStatus() const override {
        Device::printStatus();
        cout << "Made in China" << endl;
    }
};
#endif