#include <iostream>
#include <vector>
#include <memory>
#include <map>

#include "command_pattern/CommandP.h"
#include "device_hierarchy/Device.h"
#include "device_hierarchy/Light.h"
#include "device_hierarchy/Camera.h"
#include "device_hierarchy/SmokeDetector.h"
#include "device_hierarchy/GasDetector.h"
#include "device_hierarchy/TV.h"
#include "device_hierarchy/MusicPlayer.h"
#include "storage_logging/LogService.h"
#include "mode_management/Mode.cpp"
#include "state_management/ChangeState.h"

int Device::idCounter = 1;
int Light::lightId = 0;
int Camera::cameraId = 0;
int TV::tvId = 0;
int LGTV::lgtvId = 0;
int SamsungTV::samsungtvId = 0;
int SmokeDetector::smokeId = 0;
int GasDetector::gasId = 0;
int ChinaLamp::cLightId = 0;

class MySweetHome
{
private:
    std::vector<Device*> devices;
    SystemStateManager* stateManager;
	std::unique_ptr<SoundSystem> musicPlayer;
public:
    void addNewDevice(char deviceType, int deviceAmount)
    {
        if(deviceType == 'S' || deviceType == 's')
        {
            if(!musicPlayer)
            {
                musicPlayer = std::make_unique<SoundSystem>();
                std::cout << "Music Player " << " added. " << std::endl;
                LogService::getInstance()->writeLog("Music Player added.", "ADD_DEVICE");
            }
            else
            {
                std::cout << "Music Player already exists in the system." << std::endl;
            }
            musicPlayer->printStatus();
            return;
		}
        for (int i = 0; i < deviceAmount; i++)
        {
            if (deviceType == 'L' || deviceType == 'l')
            {
                devices.push_back(new Light("Light"));
				std::cout << "Light " << this->devices.back()->getId() << " added. " << std::endl;
                LogService::getInstance()->writeLog("Light " + std::to_string(this->devices.back()->getId()) + " added.", "ADD_DEVICE");
                if (this->devices.back()->getId() == 11)
                {
					devices.push_back(new ChinaLamp("China Lamp"));
                    std::cout << "China lamp " << this->devices.back()->getId() << " added. " << std::endl;
                    LogService::getInstance()->writeLog("China lamp " + std::to_string(this->devices.back()->getId()) + " added.", "ADD_DEVICE");
                }              
            }
            if (deviceType == 'C' || deviceType == 'c')
            {
                devices.push_back(new Camera("Camera"));
				std::cout << "Camera " << this->devices.back()->getId() << " added. " << std::endl;
                LogService::getInstance()->writeLog("Camera " + std::to_string(this->devices.back()->getId()) + " added.", "ADD_DEVICE");
            }
            if (deviceType == 'T' || deviceType == 't')
            {
                char tvBrand = getSafeInput<char>("Select TV Brand: (L)G, (S)amsung ");
                if (tvBrand == 'L' || tvBrand == 'l')
                {
                    devices.push_back(new LGTV("LG TV"));
                    std::cout << "LG TV" << this->devices.back()->getId() << " added. " << std::endl;
                    LogService::getInstance()->writeLog("LG TV" + std::to_string(this->devices.back()->getId()) + " added. ", "ADD_DEVICE");
                }
                else if (tvBrand == 'S' || tvBrand == 's')
                {
                    devices.push_back(new SamsungTV("Samsung TV"));
                    std::cout << "Samsung TV" << this->devices.back()->getId() << " added. " << std::endl;
                    LogService::getInstance()->writeLog("Samsung TV" + std::to_string(this->devices.back()->getId()) + " added. ", "ADD_DEVICE");
                }
            }
            if(deviceType == 'O' || deviceType == 'o')
            {
                devices.push_back(new SmokeDetector("Smoke Detector"));
                std::cout << "Smoke detector" << this->devices.back()->getId() << " added. " << std::endl;
                LogService::getInstance()->writeLog("Smoke Detector" + std::to_string(this->devices.back()->getId()) + " added. ", "ADD_DEVICE");
			}
            if(deviceType == 'G' || deviceType == 'g')
            {
                devices.push_back(new GasDetector("Gas Detector"));
                std::cout << "Gas detector" << this->devices.back()->getId() << " added. " << std::endl;
                LogService::getInstance()->writeLog("Gas detector" + std::to_string(this->devices.back()->getId()) + " added. ", "ADD_DEVICE");
			}
        }
    }
    void setStateManager(SystemStateManager* ssm)
    {
        stateManager = ssm;
    }
    void showHomeStatus()
    {
        ModeType currentMode = ModeManager::instance().getCurrentMode();
        std::cout << "--- Home Status ---" << std::endl;
        std::cout << "Current Mode: " << modeToString(currentMode) << std::endl;
        if (stateManager != nullptr) 
        {
            stateManager->showState();
        }
        else 
        {
            std::cout << "Not Set";
        }
        std::cout << std::endl;
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
            if ((*i)->getType() == deviceType && (*i)->getId() == targetId)
            {
                cout << (*i)->getFullType() << " " << targetId << " removed." << endl;
                LogService::getInstance()->writeLog((*i)->getFullType() + " " + std::to_string(targetId) + " removed.", "REMOVED_DEVICE");
                delete* i;
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
    void setAllDevicesState(char type, bool status)
    {
        char lowerType = tolower(type);
        for (auto device : devices)
        {
            if (tolower(device->getType()) == lowerType)
            {
                if (status) device->connect();
                else device->close();
            }
        }
    }
    void connect(char deviceType, int targetId)
    {
        if (deviceType == 'S' || deviceType == 's')
        {
            if (!musicPlayer)
            {
                std::cout << "Music Player connected." << std::endl;
            }
            musicPlayer->connect();
            musicPlayer->printStatus();
            return;
        }
        bool found = false;
        for (auto device : devices)
        {
            if (device->getType() == deviceType && device->getId() == targetId) {
                device->connect();
                found = true;
                LogService::getInstance()->writeLog(device->getFullType() + " " + std::to_string(targetId) + "connected.", "CONNECT_DEVICE");
                break;
            }
        }
        if (!found) {
            cout << "Device not found!" << endl;
        }
    }
    void close(char deviceType, int targetId)
    {
        if (deviceType == 'S' || deviceType == 's')
        {
            if (!musicPlayer)
            {
                musicPlayer = std::make_unique<SoundSystem>();
                std::cout << "Music Player closed." << std::endl;
            }
            musicPlayer->close();
            musicPlayer->printStatus();
            return;
        }
        bool found = false;
        for (auto device : devices)
        {
            if (device->getType() == deviceType && device->getId() == targetId) 
            {
                device->close();
                found = true;
                LogService::getInstance()->writeLog(device->getFullType() + " " + std::to_string(targetId) + "closed.", "CLOSE_DEVICE");
                break;
            }
        }
        if (!found) 
        {
            cout << "Device not found!" << endl;
        }
    }
    void setBrokenDevice(char deviceType, int targetId, std::string reason)
    {
        bool found = false;
        for (auto device : devices)
        {
            if (device->getType() == deviceType && device->getId() == targetId)
            {
                device->setBroken(reason);
                found = true;
                break;
            }
        }
        if (!found)
        {
            std::cout << "Device not found!" << endl;
        }
    }
    ~MySweetHome()
    {
        for (auto& device : devices)
        {
            delete device;
        }
        devices.clear();
    }
};
class DeviceController : public Observer {
private:
    MySweetHome* msh; 

public:
    DeviceController(MySweetHome* system) : msh(system) {}

    void update(ModeType mode) override {
        std::cout << "Mode changed to " << modeToString(mode) << std::endl;
        LogService::getInstance()->writeLog("Mode changed to " + modeToString(mode), "CHANGE_MODE");

        switch (mode) {
        case NORMAL:

            msh->setAllDevicesState('L', true);
            msh->setAllDevicesState('S', false);
            msh->setAllDevicesState('T', false);
            break;

        case EVENING:

            msh->setAllDevicesState('L', false);
            msh->setAllDevicesState('S', false);
            msh->setAllDevicesState('S', false);
            break;

        case PARTY:
            
            msh->setAllDevicesState('L', true);
            msh->setAllDevicesState('S', false);
            msh->setAllDevicesState('T', false);
            break;

        case CINEMA:
         
            msh->setAllDevicesState('L', false);
            msh->setAllDevicesState('S', true);
            msh->setAllDevicesState('T', true);
            break;
        }
    }
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
        char deviceType = getSafeInput<char>("L,l: Light | C,c: Camera | T,t: TV | O,o Smoke Detector, | G,g Gas detector: ");
        std::cout << deviceType << " ";
        int deviceAmount = getSafeInput<int>("Amount: ");
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
        char deviceType = getSafeInput<char>("L,l: Light | C,c: Camera | T,t: TV | O,o Smoke Detector, | G,g Gas detector: ");
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
		case 'O':
            selectedDevice = "Smoke Detector";
			break;
        case 'o':
			selectedDevice = "Smoke Detector";
			break;
        case 'G':
            selectedDevice = "Gas Detector";
			break;
        case 'g':
			selectedDevice = "Gas Detector";
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
        char deviceType = getSafeInput<char>("L,l: Light | C,c: Camera | T,t: TV | O,o Smoke Detector, | G,g Gas detector | S,s Sound System: ");
        if (deviceType == 'S' || deviceType == 's')
        {
            mySH->connect(deviceType, -1);
            return;
        }
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
        char deviceType = getSafeInput<char>("L,l: Light | C,c: Camera | T,t: TV | O,o Smoke Detector, | G,g Gas detector | S,s Sound System: ");
        if (deviceType == 'S' || deviceType == 's')
        {
			mySH->close(deviceType, -1);
            return;
        }
        std::cout << deviceType;
        int deviceId = getSafeInput<int>(" ID to power on: ");
        mySH->close(deviceType, deviceId);
    }
};

class ChangeMode : public Command
{
public:
    ChangeMode() {}

    void execute()
    {
        std::cout << "-----Change Mode-----" << std::endl;
        char modeType = getSafeInput<char>("N,n: Normal | E,e: Evening | P,p: Party | C,c: Cinema : ");

        ModeManager& mgr = ModeManager::instance(); 

        switch (modeType)
        {
        case 'N': case 'n':
            mgr.setMode(NORMAL);
            std::cout << "Normal mode set. " << std::endl;
            LogService::getInstance()->writeLog("Normal mode set", "MODE");
            break;
        case 'E': case 'e':
            mgr.setMode(EVENING);
            std::cout << "Evening mode set. " << std::endl;
            LogService::getInstance()->writeLog("Evening mode set.", "MODE");
            break;
        case 'P': case 'p':
            mgr.setMode(PARTY);
            std::cout << "Party mode set. " << std::endl;
            LogService::getInstance()->writeLog("Party mode set.", "MODE");
            break;
        case 'C': case 'c':
            mgr.setMode(CINEMA);
            std::cout << "Cinema mode set. " << std::endl;
            LogService::getInstance()->writeLog("Cinema mode set. ", "MODE");
            break;
        default:
            std::cout << "Invalid mode type selected. " << std::endl;
            return;
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
        std::cout << "About this application: " << std::endl <<
            "MySweetHome is a smart home management system developed by Berkan Ceylan, Orkun Karavelioðlu, Berkay Demirci, " <<
            "Erenalp Tunay, Mehmet Fatih Ünlü, Umut Baran Ulusan and Ege Býyýklý. " << std::endl <<
            "It allows users to control and monitor various smart devices in their homes, " <<
            "providing convenience, security, and energy efficiency. " << std::endl;
    }
};
class ShutDownSystem : public Command
{
public:
    void execute()
    {
        std::cout << "System is shutting down... " << std::endl;
        LogService::getInstance()->writeLog("User shutting down to system", "SYSTEM");
    }
};
class SimulatedEvent_1 : public Command
{

};
class SimulatedEvent_3 : public Command
{
private:
    MySweetHome* mySH;
public:
    SimulatedEvent_3(MySweetHome* mys) : mySH(mys) {}
    void execute()
    {
        mySH->setBrokenDevice('l', 2, "dog crushed it");
    }
};
int main()
{
    LogServiceInterface* logger = LogService::getInstance();
    bool kontrol = logger->Start();
    MySweetHome msh;
    MenuSystem menu;
    SystemStateManager ssm;
    DeviceController dc(&msh);
    ModeManager::instance().attach(&dc);
    msh.setStateManager(&ssm);
    bool isValid = true;// Komutlarý calistirdigimiz while dongusu "10" tusuna basýldýgýnda kontrolsuz cýkýs yapýyordu bu ifade ile duzeltildi.(15-12-2025 12.00) Berkan Ceylan
   
    Command* homeStatus = new ShowHomeStatus(&msh);
    Command* addDevice = new AddNewDevice(&msh);
    Command* removeDevice = new RemoveDevice(&msh);
    Command* connect = new Connect(&msh);
    Command* close = new Close(&msh);
    Command* changeMode = new ChangeMode();
    Command* changeState = new ChangeState(&ssm);
    Command* manual = new DisplayManual();
    Command* about = new DisplayAbout();
    Command* shutdown = new ShutDownSystem();
	Command* simulatedEvent3 = new SimulatedEvent_3(&msh);

    menu.assignButton(1, homeStatus);
    menu.assignButton(2, addDevice);
    menu.assignButton(3, removeDevice);
    menu.assignButton(4, connect);
    menu.assignButton(5, close);
    menu.assignButton(6, changeMode);
    menu.assignButton(7, changeState);
    menu.assignButton(8, manual);
    menu.assignButton(9, about);
    menu.assignButton(10, shutdown);
	menu.assignButton(13, simulatedEvent3); // Simulated Event 3 

    while (isValid)
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
		if (kontrol == 1) logger->writeLog("User selected command " + std::to_string(choice), "SYSTEM");

        menu.pressButton(choice);

        if (choice == 10) isValid = false;// choice "10" ise guvenli bir sekilde whiledan cýkýs yapýlýyor.

        std::cout << "-------------------------------------" << std::endl;
    }
    menu.clearCommands();

    logger->Close();
    return 0;
}