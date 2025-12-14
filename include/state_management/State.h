#ifndef STATE_H
#define STATE_H

#include <string>

class SystemStateManager; 

class State
{
public:
    virtual ~State() {}
    virtual void enter(SystemStateManager* manager) = 0;
    virtual std::string getName() const = 0;
};

#endif
