#include <iostream>
#include <vector>
#include <map>
#include "Device.h"
class Device
{
public:
    std::string name;
    bool isOn = true;
    int id = 1;
    virtual void showStatus() = 0;
    virtual void powerOn() = 0;
    virtual void powerOff() = 0;

};
class Light : public Device
{
    void showStatus()
    {
        if (!this->isOn)
        {
            std::cout << "Lights " << this->id << " is off. " << std::endl;
        }
        else
        {
            std::cout << "Lights " << this->id << " is on. " << std::endl;
        }
    }
    void powerOn()
    {
        if (!this->isOn)
        {
            this->isOn = true;
            std::cout << "Light " << this->id << " power on " << std::endl;
        }
    }
    void powerOff()
    {
        if (this->isOn)
        {
            this->isOn = false;
            std::cout << "Light " << this->id << " power off " << std::endl;
        }
    }
    ~Light()
    {
        std::cout << "Light object(s) destroyed " << std::endl;
    }
};
class Camera : public Device
{
    void showStatus()
    {
        if (!this->isOn)
        {
            std::cout << "Camera " << this->id << " is off. " << std::endl;
        }
        else
        {
            std::cout << "Camera " << this->id << " is on. " << std::endl;

        }
    }
    void powerOn()
    {
        if (!this->isOn)
        {
            this->isOn = true;
            std::cout << "Camera  " << this->id << " power on " << std::endl;
        }

    }
    void powerOff()
    {
        if (this->isOn)
        {
            this->isOn = false;
            std::cout << "Camera " << this->id << " power off " << std::endl;
        }
    }
    ~Camera()
    {
        std::cout << "Camera object(s) destroyed " << std::endl;

    }
};
class MySweetHome
{
private:
    std::vector<Device*> devices;
public:
    void addNewDevice(char deviceType, int deviceAmount)
    {
        for (int i = 0; i < deviceAmount; i++)
        {
            if (deviceType == 'L' || deviceType == 'l')
                devices.push_back(new Light());
            if (deviceType == 'C' || deviceType == 'c')
                devices.push_back(new Camera());
        }
        std::cout << "Added " << deviceAmount << " " << deviceType << std::endl;
    }
    Device* getDevice(int id)
    {
        if (id >= 0 && id < devices.size())
        {
            return devices[id];
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
            std::cout << "[" << i + 1 << "]" << " ";
            devices[i]->showStatus();
        }
    }
    void removeDevice(size_t index)
    {
        if (index < devices.size())
        {
			std::string deletedDeviceName = devices[index]->name;
            delete devices[index];
            devices.erase(devices.begin() + index);
            std::cout << deletedDeviceName << " is removed. " << std::endl;
        }
        else
        {
			std::cout << "Invalid device index. " << std::endl;
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

        std::cout << "L: Light, C: Camera " << std::endl;
        std::cin >> deviceType;

        std::cout << deviceType << " amount: ";
        std::cin >> deviceAmount;

        mySH->addNewDevice(deviceType, deviceAmount);
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
            device->powerOn();
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
            device->powerOff();
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
    Command* manual = new DisplayManual();
    Command* about = new DisplayAbout();

    menu.assignButton(1, homeStatus);
    menu.assignButton(2, addDevice);
    menu.assignButton(8, manual);
    menu.assignButton(9, about);
    ;
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
        /*switch (choice)
        {
            case 1:
            {
                std::cout << "Home status...\n";
                msh.showHomeStatus();
                break;
            }
            case 2:
            {
                std::cout << "Add device: (L)ight, (C)amera" << std::endl;
                char deviceChoice;
                std::cin >> deviceChoice;
                if (deviceChoice == 'L' || deviceChoice == 'l')
                {
                    Light* newLight = new Light();
                    msh.addNewDevice(newLight);
                    newLight->id += lightId;
                    lightId++;
                    std::cout << "Light " << newLight->id << " has been added. " << std::endl;
                }
                if (deviceChoice == 'C' || deviceChoice == 'c')
                {
                    Camera* newCamera = new Camera();
                    msh.addNewDevice(newCamera);
                    newCamera->id += cameraId;
                    cameraId++;
                    std::cout << "Camera " << newCamera->id << " has been added. " << std::endl;
                }
                break;
            }
            case 3:
            {
                std::cout << "Remove device...\n";
                break;
            }
            case 4:
            {
                std::cout << "Power on, select device: (L)ight, (C)amera\n";
                std::cin >> deviceChoice;
                std::cout << "Enter device id: " << std::endl;
                std::cin >> id;
                Device* targetDevice = msh.getDevice(id - 1);
                if (targetDevice != NULL)
                {
                    Command* powerOnCmd = new TurnOnPower(targetDevice);
                    powerOnCmd->execute();
                    delete powerOnCmd;
                }
                else
                {
                    std::cout << "Invalid device id " << std::endl;
                }
                break;
            }
            case 5:
            {
                std::cout << "Power off, select device: (L)ight, (C)amera\n";
                std::cin >> deviceChoice;
                std::cout << "Enter device id: " << std::endl;
                std::cin >> id;
                Device* targetDevice = msh.getDevice(id - 1);
                if (targetDevice != NULL)
                {
                    Command* powerOffCmd = new TurnOffPower(targetDevice);
                    powerOffCmd->execute();
                    delete powerOffCmd;
                }
                else
                {
                    std::cout << "Invalid device id " << std::endl;
                }
                break;
            }
            case 6:
            {
                std::cout << "Change mode...\n";
                break;
            }
            case 7:
            {
                std::cout << "Change state...\n";
                break;
            }
            case 8:
            {
                std::cout << "Manual...\n";
                break;
            }
            case 9:
            {
                std::cout << "About MySweetHome.";
                break;
            }
            case 10:
            {
                return 0;
            }
            default:
                std::cout << "Invalid choice!\n";
                break;
        }*/
        std::cout << "-------------------------------------" << std::endl;
    }


    return 0;
}
