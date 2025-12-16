#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <map>
#include <limits>

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
            std::cout << "Ivalid input \n";
            clearCin();
        }
        else
        {
            clearCin();
            return value;
        }
    }
}
class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
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
#endif 
