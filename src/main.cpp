#include <iostream>
#include <vector>
#include <map>

#include "device_hierarchy/Device.h"
#include "device_hierarchy/Light.h"
#include "device_hierarchy/Camera.h"
#include "device_hierarchy/TV.h"
struct DeviceStruct
{
    int id;
    std::string type;
};
int id = 1;
char deviceType2 = NULL;
class MySweetHome
{
private:
    std::vector<DeviceStruct*> devices;
public:
    void addNewDevice(char deviceType, int deviceAmount)
    {
        if (deviceType2 != deviceType) {
            id = 1;
        }
        for (int i = 0; i < deviceAmount; i++)
        {
            if (deviceType == 'L' || deviceType == 'l')
            {
                //devices.push_back(new Light("Light"));
                devices.push_back(new DeviceStruct({ id++,"Light" }));
                deviceType2 = deviceType;
            }    
            if (deviceType == 'C' || deviceType == 'c')
            {
                //devices.push_back(new Camera("Camera"));
                devices.push_back(new DeviceStruct({ id++,"Camera" }));
                deviceType2 = deviceType;

            }
            if (deviceType == 'T' || deviceType == 't')
            {
				char tvBrand;
				std::cout << "Select TV Brand: (L)G, (S)amsung " << std::endl;
				std::cin >> tvBrand;
                if (tvBrand == 'L' || tvBrand == 'l')
                {
                    //devices.push_back(new LGTV("LG TV"));
                    devices.push_back(new DeviceStruct({ id++,"LG TV" }));
                    deviceType2 = deviceType;
                    std::cout << "LG TV added. " << std::endl;
                }
                else if (tvBrand == 'S' || tvBrand == 's')
                {
                    //devices.push_back(new SamsungTV("Samsung TV"));
                    devices.push_back(new DeviceStruct({ id++,"Samsung" }));
                    deviceType2 = deviceType;
                    std::cout << "Samsung TV added. " << std::endl;
                }
            }
        }
        std::cout << "Added " << deviceAmount << " " << deviceType << std::endl;
    }
    Device* getDevice(int id)
    {
        if (id >= 0 && id < devices.size())
        {
            //return devices[id];
        }
        return NULL;
    }

    int getDeviceCount()
    {
        return devices.size();
    }
    void showHomeStatus()
    {
        std::cout << "--- Home Status ---" << std::endl;
        for (size_t i = 0; i < devices.size(); i++)
        {
            //devices[i]->printStatus();
            printStatus(devices[i]);
        }
    }
    void removeDevice(size_t index)
    {
        if (index < devices.size())
        {
            //std::cout << devices[index]->getName() << " " << index << " is removed. " << std::endl;
            delete devices[index];
            devices.erase(devices.begin() + index);
        }
    }
    ~MySweetHome()
    {
        std::cout << "System shutting down... " << std::endl;
        for (auto& device : devices)
        {
            delete device;
        }
        devices.clear();
    }
};

class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

class ShowHomeStatus : public Command
{
private:
    MySweetHome* mySH;
public:
    ShowHomeStatus(MySweetHome* msh) : mySH(msh) {}
    void execute()
    {
        mySH->showHomeStatus();
    }
};

class AddNewDevice : public Command
{
private:
    MySweetHome* mySH;
public:
    AddNewDevice(MySweetHome* msh) : mySH(msh) {}
    void execute()
    {
        char deviceType;
        int deviceAmount;
        std::cout << "-----Add Device(s)-----" << std::endl;

        std::cout << "L,l: Light, C,c: Camera, T,t: TV " << std::endl;
        std::cin >> deviceType;

        std::cout << deviceType << " amount: ";
        std::cin >> deviceAmount;

        mySH->addNewDevice(deviceType, deviceAmount);
    }
};
class RemoveDevice : public Command
{
    private:
		MySweetHome* mySH;
    public:
        RemoveDevice(MySweetHome* msh) : mySH(msh) {}
        void execute()
        {
            int deviceId;
            std::cout << "Enter device id to remove: " << std::endl;
            std::cin >> deviceId;
            mySH->removeDevice(deviceId);
		}
};
class TurnOnPower : public Command
{
private:
    Device* device;
public:
    TurnOnPower(Device* dev) : device(dev) {}
    void execute()
    {
        if (device)
        {
            device->connect();
            std::cout << "Sa";
        }
    }
};

class TurnOffPower : public Command
{
private:
    Device* device;
public:
    TurnOffPower(Device* dev) : device(dev) {}
    void execute()
    {
        if (device)
        {
            device->close();
        }
    }
};

class DisplayManual : public Command
{
public:
    void execute()
    {
        std::cout << "How to use MySweetHome App: " << std::endl <<
            "[1] Enter a number from 1 to 10 depends on which command you want to execute. " << std::endl <<
            "[2] Depending on the command, you might need to choose a device. " << std::endl <<
            "[3] App is going to get command done for you. " << std::endl <<
            "[4] Select 0 to quit the app. " << std::endl;
    }
};

class DisplayAbout : public Command
{
public:
    void execute()
    {
        std::cout << " " << std::endl;
    }
};
class ShutDownSystem : public Command
{
    public:
    void execute()
    {
        std::cout << "System is shutting down... " << std::endl;
        exit(0);
    }
};
class MenuSystem
{
private:
    std::map<int, Command*> events;

public:
    void assignButton(int key, Command* cmd)
    {
        events[key] = cmd;
    }
    void pressButton(int key)
    {
        if (events.find(key) != events.end())
        {
            events[key]->execute();
        }
        else
        {
            std::cout << "There is no such executable event " << std::endl;
        }
    }
    void clearCommands()
    {
        events.clear();
    }
};

int main()
{

    MySweetHome msh;
    MenuSystem menu;

    Command* homeStatus = new ShowHomeStatus(&msh);
    Command* addDevice = new AddNewDevice(&msh);
	Command* removeDevice = new RemoveDevice(&msh);
	Command* connect = new TurnOnPower(nullptr);
    Command* manual = new DisplayManual();
    Command* about = new DisplayAbout();
	Command* shutdown = new ShutDownSystem();

    menu.assignButton(1, homeStatus);
    menu.assignButton(2, addDevice);
	menu.assignButton(3, removeDevice);
    menu.assignButton(8, manual);
    menu.assignButton(9, about);
    menu.assignButton(10, shutdown);
    
    char deviceChoice;
    int id;
    int lightId = 0;
    int cameraId = 0;

    while (true)
    {
        std::cout << "MY SWEET HOME (MSH)" << std::endl <<
            "[1] Get Home Status(Show state and mode, information about sensors and actuators)" << std::endl <<
            "[2] Add Device - (L)ight, Smoke& Gas(D)etectors, (C)amera, (T)V" << std::endl <<
            "[3] Remove Device - (L)ight, Smoke& Gas(D)etectors, (C)amera, (T)V" << std::endl <<
            "[4] Power on Device - (L)ight, Smoke& Gas(D)etectors, (C)amera, (T)V, (S)ound System" << std::endl <<
            "[5] Power off Device - (L)ight, Smoke& Gas(D)etectors, (C)amera, (T)V, (S)ound System" << std::endl <<
            "[6] Change Mode - (N)ormal, (E)vening, (P)arty, (C)inema" << std::endl <<
            "[7] Change State - (N)ormal, (H)igh Performance, (L)ow Power, (S)leep, (P)revious one" << std::endl <<
            "[8] Manual(Display manual)" << std::endl <<
            "[9] About(information about product and developers)" << std::endl <<
            "[10] Shutdown(shut down the system)" << std::endl;
        short int choice;
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Number only (1-10) " << std::endl;
            continue;
        }
        menu.pressButton(choice);

        std::cout << "-------------------------------------" << std::endl;
    }


    return 0;
}