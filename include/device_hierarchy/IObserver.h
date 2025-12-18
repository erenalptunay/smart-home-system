#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <string>
using namespace std;

// Bildirim alacak herkesin uymasý gereken kurallar
class IObserver {
public:
    virtual ~IObserver() {}
    // Cihazdan gelen bildirimleri alan metot
    virtual void update(const string& deviceName, const string& message) = 0;
};

#endif