#include "LogService.h"

LogServiceInterface::~LogServiceInterface() {}

LogService::LogService() {}

LogService::~LogService() { Close(); }

LogService& LogService::getInstance() {
	static LogService instance;
	return instance;
}

bool LogService::Start() {
	m_logfile.open("app.log", std::ios::app); //Dosyayý ekleme modunda açtýk

	if (m_logfile.is_open() == 1)
	{
		std::cout << "Log dosyasý basarili bir sekilde acildi." << std::endl;
		return true;
	}
	else
	{
		m_logfile.open("app.log", std::ios::out);
		if (m_logfile.is_open() == 1)
		{
			std::cout << "Log dosyasý basarili bir sekilde olusturuldu." << std::endl;
			return true;
		}
		else 
		{
			std::cout << "Log dosyasý olusturulamadý yada acilamadi" << std::endl;
			return false;
		}
	}
}
void LogService::writeLog(const std::string& message) {

}

void LogService::Close() {

}