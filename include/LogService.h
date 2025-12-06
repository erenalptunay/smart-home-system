#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "LogServiceInterface.h"
#include <fstream>
//#include <string>

class LogService : public LogServiceInterface
{
public:
	static LogService& getInstance();

	bool Start() override;
	void writeLog(const std::string& message) override;
	void Close() override;

private:
	std::fstream m_logfile;
	LogService();
	~LogService();

	LogService(const LogService&) = delete;
	LogService& operator = (const LogService&) = delete;

	const std::string getCurrentTime();
	const std::string jsonFormatConverter(const std::string& rawMessage);

};


#endif // !LOGSERVICE_H
