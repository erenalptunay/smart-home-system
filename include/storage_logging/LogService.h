#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "storage_logging/LogServiceInterface.h"
#include <fstream>
#include <vector>
#include <chrono>
#include <format>

class LogService : public LogServiceInterface
{
public:
	static LogService *getInstance();

	bool Start() override;
	void writeLog(const std::string& message, std::string source) override;
	void Close() override;

private:
	std::fstream m_logfile;
	static LogService* instance;

	enum LogTimeFormat {
		FULL_TIME,
		DATE_ONLY,
		TIME_ONLY
	};
	enum LogMessageType {
		Initialization,
		NewLogEntry
	};

	struct Item
	{
		int LogNo;
		std::string Time;
		std::string Source;
		std::string Message;
	};

	struct DataModel
	{
		std::string DateTime;
		std::vector<Item> Logs;
	};

	DataModel m_dataModel;
	Item m_itemModel;


	LogService();
	~LogService();

	LogService(const LogService&) = delete;
	LogService& operator = (const LogService&) = delete;

	const std::string getCurrentTime(LogTimeFormat format);
	const std::string jsonFormatConverter(LogMessageType type);

};


#endif // !LOGSERVICE_H
