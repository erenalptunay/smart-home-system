#include "../../include/detection_system/AlarmHandler.h"

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
