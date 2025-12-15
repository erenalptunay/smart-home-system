#include "../../include/detection_system/AlarmHandler.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

// Linux implementation of _kbhit
int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) {
        // Use termios to turn off line buffering
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

// Linux implementation of _getch
char _getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}
#endif

using namespace std;

void AlarmHandler::handleRequest() {
    cout << "[System] Alarm activated! You have 10 seconds to cancel..." << endl;
    cout << "[System] Press 's' to stop the alarm." << endl;

    auto startTime = std::chrono::steady_clock::now();
    bool interrupted = false;

    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

        if (elapsed >= 10) {
            cout << "\n[System] 10 seconds elapsed. Alarm sequence continuing..." << endl;
            break;
        }

        // Non-blocking input check (Windows specific)
        if (_kbhit()) {
            char input = _getch();
            if (input == 's' || input == 'S') {
                cout << "\n[System] Alarm stopped by user. Sequence interrupted." << endl;
                interrupted = true;
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (!interrupted) {
        EmergencyHandler::handleRequest();
    }
}
