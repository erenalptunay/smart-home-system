#include <iostream>
#include <vector>
#include <map>

#include "device_hierarchy/Device.h"
#include "device_hierarchy/Light.h"
#include "device_hierarchy/Camera.h"
#include "device_hierarchy/TV.h"
#include <storage_logging/LogService.h>

int Device::idCounter = 1;
int Light::lightId = 0;
int Camera::cameraId = 0;
int TV::tvId = 0;
int LGTV::lgtvId = 0;
int SamsungTV::samsungtvId = 0;

void clearCin()
{
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
template<typename T>
T getSafeInput(const std::string& message)
{
    T value;

    while (true)
    {
        std::cout << message;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cout << "Gecersiz giris!\n";
            clearCin();
        }
        else
        {
            clearCin(); 
            return value;
        }
    }
}
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
            {
                devices.push_back(new Light("Light"));
            }    
            if (deviceType == 'C' || deviceType == 'c')
            {
                devices.push_back(new Camera("Camera"));
            }
            if (deviceType == 'T' || deviceType == 't')
            {
				char tvBrand = getSafeInput<char>("Select TV Brand: (L)G, (S)amsung ");
                if (tvBrand == 'L' || tvBrand == 'l')
                {
                    devices.push_back(new LGTV("LG TV"));
                    std::cout << "LG TV added. " << std::endl;
                }
                else if (tvBrand == 'S' || tvBrand == 's')
                {
                    devices.push_back(new SamsungTV("Samsung TV"));
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
            devices[i]->printStatus();
        }
    }
    void removeDevice(char deviceType, int targetId)
    {
		bool found = false;
        for (auto i = devices.begin(); i != devices.end(); i++)
        {
            if ((*i)->getType() == deviceType  && (*i)->getId() == targetId)
            {
                cout << (*i)->getFullType() << " " << targetId << " removed." << endl;
                delete *i;
				devices.erase(i);
				found = true;
				break;
            }
        }
        if (!found)
        {
			std::cout << "Device " << deviceType << " " << targetId << " not found. " << std::endl;
        }
    }
    void connect(char deviceType, int targetId)
    {
        bool found = false;
        for (auto device : devices) 
        {
            if (device->getType() == deviceType && device->getId() == targetId) {
                device->connect(); 
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Device not found!" << endl;
        }
    }
    void close(char deviceType, int targetId)
    {
        bool found = false;
        for (auto device : devices) 
        {
            if (device->getType() == deviceType && device->getId() == targetId) {
                device->close(); 
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Device not found!" << endl;
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
        std::cout << "-----Add Device(s)-----" << std::endl;
        char deviceType = getSafeInput<char>("L,l: Light | C,c: Camera | T,t: TV : ");
        std::cout << deviceType << " ";
        int deviceAmount = getSafeInput<int>("amount: ");
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
			std::string selectedDevice;
            
			std::cout << "-----Remove Device-----" << std::endl;
            char deviceType = getSafeInput<char>("L,l: Light | C,c: Camera | T,t: TV : ");
            switch (deviceType)
            {
			    case 'L':
					selectedDevice = "Light";
                    break;
				case 'l':
                    selectedDevice = "Light";
					break;
                case 'C':
					selectedDevice = "Camera";
                    break;
				case 'c':
					selectedDevice = "Camera";
                    break;
				case 'T':
                    selectedDevice = "TV";
					break;
                case 't':
					selectedDevice = "TV";
                    break;
				default:
                    std::cout << "Invalid device type selected. " << std::endl;
					return;
            }
			std::cout << selectedDevice;
            int deviceId = getSafeInput<int>(" ID to remove: ");
            mySH->removeDevice(deviceType, deviceId);
		}
};
class Connect : public Command
{
private:
    MySweetHome* mySH;
public:
    Connect(MySweetHome* msh) : mySH(msh) {}
    void execute()
    {
		std::cout << "-----Power On Device-----" << std::endl;
        char deviceType = getSafeInput<char>("L,l: Light | C,c: Camera | T,t: TV : ");
		std::cout << deviceType;
        int deviceId = getSafeInput<int>(" ID to power on: ");
		mySH->connect(deviceType, deviceId);
    }
};

class Close : public Command
{
private:
	MySweetHome* mySH;
public:
    Close(MySweetHome* msh) : mySH(msh) {}
    void execute()
    {
		std::cout << "-----Power Off Device-----" << std::endl;
        char deviceType = getSafeInput<char>("L,l: Light | C,c: Camera | T,t: TV : ");
        std::cout << deviceType;
        int deviceId = getSafeInput<int>(" ID to power on: ");
		mySH->close(deviceType, deviceId);
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
    LogServiceInterface *logger = LogService::getInstance();
    bool kontrol = logger->Start();
    MySweetHome msh;
    MenuSystem menu;
    
    Command* homeStatus = new ShowHomeStatus(&msh);
    Command* addDevice = new AddNewDevice(&msh);
	Command* removeDevice = new RemoveDevice(&msh);
	Command* connect = new Connect(&msh);
	Command* close = new Close(&msh);
    Command* manual = new DisplayManual();
    Command* about = new DisplayAbout();
	Command* shutdown = new ShutDownSystem();

    menu.assignButton(1, homeStatus);
    menu.assignButton(2, addDevice);
	menu.assignButton(3, removeDevice);
	menu.assignButton(4, connect);
	menu.assignButton(5, close);
    menu.assignButton(8, manual);
    menu.assignButton(9, about);
    menu.assignButton(10, shutdown);
    
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

        short int choice = getSafeInput<int>("Select a command: ");
        if (kontrol == 1) logger->writeLog("a", "");

        menu.pressButton(choice);

        std::cout << "-------------------------------------" << std::endl;
    }
	menu.clearCommands();
    return 0;
}