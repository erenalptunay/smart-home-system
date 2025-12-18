#include "../../include/detection_system/LightOnHandler.h"
#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

// Linux implementation of _kbhit (reused static)
static int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

static char _getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
    return (buf);
}
#endif

using namespace std;

LightOnHandler::LightOnHandler(const vector<Light*>& homeLights) : lights(homeLights) {}

void LightOnHandler::handleRequest() {
    cout << "[System] Flashing lights... (Press 's' to stop)" << endl;
    
    bool interrupted = false;
    // Flash lights 5 times with 1 second interval (Reduced to half)
    for (int i = 0; i < 5; ++i) {
        cout << "Lights ON" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        cout << "Lights OFF" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Check for user interrupt (LLR-44, LLR-45)
        if (_kbhit()) {
            char input = _getch();
            if (input == 's' || input == 'S') {
                cout << "\n[System] Light sequence stopped by user." << endl;
                cout << "[System] Fire Station was NOT notified." << endl;
                interrupted = true;
                break;
            }
        }
    }

    if (!interrupted) {
        EmergencyHandler::handleRequest();
    }
}
