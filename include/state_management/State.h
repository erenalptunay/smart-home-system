#ifndef STATE_H
#define STATE_H

#include <string>

class SystemStateManager; 
class DeviceController;

class State
{
public:
    virtual ~State() {}
    virtual void enter(SystemStateManager* , DeviceController*) = 0;
    virtual std::string getName() const = 0;
};

#endif
