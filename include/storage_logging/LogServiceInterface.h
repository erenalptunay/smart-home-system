#ifndef LOGSERVICEINTERFACE_H
#define LOGSERVICEINTERFACE_H

#include <iostream>

class LogServiceInterface
{
public:
	virtual ~LogServiceInterface() = 0;
	virtual bool Start() = 0;
	virtual void writeLog(const std::string& message, std::string source) = 0;
	virtual void Close() = 0;
};



#endif // !LOGSERVICEINTERFACE_H
