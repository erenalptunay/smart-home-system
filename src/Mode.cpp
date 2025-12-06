#include <iostream>
#include <vector>
//using namespace std;

enum ModeType {
    NORMAL,
    EVENING,
    PARTY,
    CINEMA
};

class Observer {
public:
    virtual void update(ModeType mode) = 0;
    virtual ~Observer() {}
};

class DeviceController : public Observer {
private:
    bool light;
    bool tv;
    bool music;
    bool camera;
    bool detector;

public:
    DeviceController() {
        light = false;
        tv = false;
        music = false;
        camera = true;      // her zaman açık
        detector = true;    // her zaman açık
    }

    void setLight(bool on)   { light = on; }
    void setTV(bool on)      { tv = on; }
    void setMusic(bool on)   { music = on; }
    void setCamera(bool on)  { camera = on; }
    void setDetector(bool on){ detector = on; }

    // Observer Pattern 
    void update(ModeType mode) override {
        switch (mode) {
            case NORMAL:
                setLight(true);
                setTV(false);
                setMusic(false);
                break;

            case EVENING:
                setLight(false);
                setTV(false);
                setMusic(false);
                break;

            case PARTY:
                setLight(true);
                setTV(false);
                setMusic(true);
                break;

            case CINEMA:
                setLight(false);
                setTV(true);
                setMusic(false);
                break;
        }

        setCamera(true);
        setDetector(true);

        /*
        cout << "[DeviceController] Yeni mod uygulandi: "
             << modeToString(mode) << endl;
             */
    }

    string modeToString(ModeType m) {
        switch(m){
            case NORMAL: return "NORMAL";
            case EVENING: return "EVENING";
            case PARTY: return "PARTY";
            case CINEMA: return "CINEMA";
        }
        return "UNKNOWN";
    }

    /* Test 
    void printStatus() {
        cout << "Light   : " << (light ? "ON" : "OFF") << endl;
        cout << "TV      : " << (tv ? "ON" : "OFF") << endl;
        cout << "Music   : " << (music ? "ON" : "OFF") << endl;
        cout << "Camera  : " << (camera ? "ON" : "OFF") << endl;
        cout << "Detector: " << (detector ? "ON" : "OFF") << endl;
    }*/
};

class ModeManager {
private:
    ModeType currentMode;
    vector<Observer*> observers;

    // Singleton 
    ModeManager() {
        currentMode = NORMAL;
    }

    static ModeManager* instancePtr;

public:

    static ModeManager* instance() {
        if (instancePtr == nullptr)
            instancePtr = new ModeManager();
        return instancePtr;
    }

    void attach(Observer* obs) {
        observers.push_back(obs);
    }

    void notify() {
        for (auto obs : observers)
            obs->update(currentMode);
    }

    void setMode(ModeType newMode) {
        currentMode = newMode;
        cout << "\n[ModeManager] Mod değişti → "
             << modeToString(currentMode) << endl;
        notify();
    }

    string modeToString(ModeType m) {
        switch(m){
            case NORMAL: return "NORMAL";
            case EVENING: return "EVENING";
            case PARTY: return "PARTY";
            case CINEMA: return "CINEMA";
        }
        return "UNKNOWN";
    }
};

// Singleton başlangıcı
ModeManager* ModeManager::instancePtr = nullptr;


