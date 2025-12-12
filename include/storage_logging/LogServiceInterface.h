#ifndef LOGSERVÝCEINTERFACE_H
#define LOGSERVÝCEINTERFACE_H

#include <iostream>

class LogServiceInterface
{
public:
	virtual ~LogServiceInterface() = 0;
	virtual bool Start() = 0;
	virtual void writeLog(const std::string& message) = 0;
	virtual void Close() = 0;
};



#endif // !LOGSERVÝCEINTERFACE_H
