#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include "Device.h"

class Light : public Device {
private:
    int brightness; 
    string color;   
    static int lightId; //ID'yi doðru yönetmek için, her cihaz için tanýmla, static olmasýna dikkat et

public:
    Light(string n, string c = "White", int b = 100)
		: Device(n), color(c), brightness(b) {	
		//DEÐÝÞÝKLÝK
        lightId++;     
		this->id = lightId; //ID'yi doðru yönetmek için, her cihaz için tanýmla bir üst satýr dahil
		this->type = 'l'; //mainde bu karakterlerle çaðýrýyoruz
    }

    // Prototype Pattern 
    Device* clone() const {
        return new Light(*this);
    }
    string getFullType() const { //Device.h de açýkladým
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

#endif