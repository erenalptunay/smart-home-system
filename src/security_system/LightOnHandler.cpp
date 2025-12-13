#include "LightOnHandler.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
// #include "Light.h" kaldýrýldý, çünkü Light Device.h içinde

LightOnHandler::LightOnHandler(const std::vector<Device*>& allDevices) : allDevices_(allDevices) {}

void LightOnHandler::handleRequest(SecurityEvent event) {
    if (event == SecurityEvent::MotionDetected) {
        std::cout << "\n--- [Security Step 2] LightOnHandler activated. ---" << std::endl;

        for (Device* device : allDevices_) {
            // LightOnHandler.cpp içinde (Örnek)
            Light* light = dynamic_cast<Light*>(device);

            if (light && light->isActive()) {
                light->turnOn();
                // Light::getId() metodunu çaðýrýrken:
                std::cout << "  - Activated Light (ID: " << light->getId() << ")." << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Lights On sequence ended." << std::endl;

        BaseHandler::handleRequest(event);
    }
    else {
        BaseHandler::handleRequest(event);
    }
}