#include "storage_logging/LogService.h"

LogServiceInterface::~LogServiceInterface() {}

LogService* LogService::instance = NULL;

LogService::LogService() {}

LogService::~LogService()
{
	std::cout << "Destructor is running" << std::endl;
	Close();
}

LogService* LogService::getInstance() {
	if (NULL == instance) {
		instance = new LogService();
	}
	return instance;
}

bool LogService::Start() {
	m_logfile.open("applog.json", std::ios::in | std::ios::out); //Dosyayý ekleme modunda açtýk
	bool status = false;


	if (m_logfile.is_open() == 1)
	{
		std::cout << "The log file was successfully opened." << std::endl;
		status = true;
	}
	else
	{
		m_logfile.open("applog.json", std::ios::out | std::ios::in | std::ios::trunc);
		if (m_logfile.is_open() == 1)
		{
			std::cout << "The log file was successfully created." << std::endl;
			status = true;
		}
		else
		{
			std::cout << "The log file could not be created or opened." << std::endl;
			status = false;
		}
	}

	if (status)
		LogService::writeLog("", "");

	return status;

}
const std::string LogService::getCurrentTime(LogTimeFormat format) {
	auto now = std::chrono::system_clock::now();
	auto zoned_time = std::chrono::zoned_time{//(zoned_time,format) özellikleri C++17 sürümünde bulunmamaktadýr.
		std::chrono::current_zone(),// Hata çözümüm için ayarlardan "C++ Language Standart" 20 ve üstü seçilmelidir.
		now
	};
	std::string formatStr;

	switch (format) {
	case LogTimeFormat::DATE_ONLY:
		return std::format("{:%Y-%m-%d}", zoned_time);
	case LogTimeFormat::TIME_ONLY:
		return std::format("{:%H:%M:%S}", zoned_time);

	case LogTimeFormat::FULL_TIME:
		return std::format("{:%Y-%m-%d %H:%M:%S}", zoned_time);
	default:
		return std::format("{:%Y-%m-%d %H:%M:%S}", zoned_time);
	}
}

const std::string LogService::jsonFormatConverter(LogMessageType type) {

	std::stringstream json;

	if (type == Initialization)
	{
		m_logfile.seekg(0, std::ios::end);
		long size = m_logfile.tellg();

		if (size == 0) {

			json << "[\n";
		}
		else
		{
			json << ",\n";
		}
		json << "\t\{\n";
		json << "\t\t\"Date\": \"" << m_dataModel.DateTime << "\",\n";
		json << "\t\t\"Logs\": []\n";
		json << "\t\}\n";
		json << "]";
	}
	else if (type == NewLogEntry)
	{
		json << "\n\t\t\t{\n";
		json << "\t\t\t\t\"LogNo\": \"" << m_itemModel.LogNo << "\",\n";
		json << "\t\t\t\t\"Time\": \"" << m_itemModel.Time << "\",\n";
		json << "\t\t\t\t\"Source\": \"" << m_itemModel.Source << "\",\n";
		json << "\t\t\t\t\"Message\": \"" << m_itemModel.Message << "\"\n";
		json << "\t\t\t}";
	}
	m_logfile.seekg(0, std::ios::beg);
	return json.str();
}

void LogService::writeLog(const std::string& message, std::string source) {

	if (!m_logfile.is_open())
	{
		std::cout << "Log file is closed" << std::endl;
		return;
	}


	std::string dbMessage;

	if (message == "") {

		m_dataModel.DateTime = getCurrentTime(FULL_TIME);

		dbMessage = jsonFormatConverter(Initialization);


		if (m_logfile.peek() != std::ifstream::traits_type::eof()) {
			m_logfile.seekg(0, std::ios::end);
			long fileSize = m_logfile.tellg();
			m_logfile.seekp(fileSize - 3);
		}
		else {

			m_logfile.seekg(0, std::ios::end);
		}

		try
		{
			m_logfile << dbMessage;
		}
		catch (const std::exception& message)
		{
			std::cout << "Could not write log to database : " << message.what() << std::endl;
		}


		m_logfile.flush();
		std::cout << "The main log object was successfully opened" << std::endl;

		m_logfile.clear();
		m_logfile.seekp(0, std::ios::beg);
	}
	else
	{
		m_itemModel.LogNo = m_dataModel.Logs.size() + 1;
		m_itemModel.Time = getCurrentTime(LogTimeFormat::TIME_ONLY);
		m_itemModel.Source = source;
		m_itemModel.Message = message;

		std::stringstream buffer;
		buffer << m_logfile.rdbuf();
		std::string file_content = buffer.str();
		m_logfile.flush();
		m_logfile.clear();
		m_logfile.seekp(0, std::ios::beg);

		std::string date_search = /*"2025-12-07";*/"\"Date\": \"" + m_dataModel.DateTime + "\"";
		std::string new_log_block = jsonFormatConverter(NewLogEntry);
		std::string updated_content;

		size_t start_pos_of_object = std::string::npos; //npos olarak baþlatýyoruz. (Bulunamadý)
		size_t lines_start_pos = std::string::npos;
		size_t closing_bracket_pos = std::string::npos;
		size_t last_brace_pos = std::string::npos;
		std::string part_before_insertion;
		std::string part_after_insertion;

		try
		{
			start_pos_of_object = file_content.find(date_search);//Ekleme yapýlacak ana nesneyi buluyor.
			if (start_pos_of_object == std::string::npos) {
				throw std::runtime_error("The date object could not be found.");
			}

			lines_start_pos = file_content.find("\"Logs\": [", start_pos_of_object);//Loglarýn ekleneceði diziyi konumlandýrýyoruz.
			if (lines_start_pos == std::string::npos) {
				throw std::runtime_error("The ‘Logs’ series could not be found.");
			}

			closing_bracket_pos = file_content.find(']', lines_start_pos);//Ekleme noktasýný ("Logs":[ ifadesinin "]") bulur.
			if (closing_bracket_pos == std::string::npos) {
				throw std::runtime_error("Could not find the end of the ‘Logs’ series.");
			}

			part_before_insertion = file_content.substr(0, closing_bracket_pos);//Dosyanýn baþlangýcýndan, bulunan kapanýþ parantezine kadar olan tüm kýsmý alýr.
			part_after_insertion = file_content.substr(closing_bracket_pos);//Kapanýþ parantezinden (]) baþlayarak dosyanýn sonuna kadar olan kýsmý alýr.
			last_brace_pos = part_before_insertion.rfind('}');//part_before_insertion içinde, kapanýþ parantezinden hemen önceki kýsýmda en son gelen } karakterini arar.

		}
		catch (const std::exception& message)
		{
			std::cerr << "A JSON format/string manipulation error occurred while writing the log: "
				<< message.what() << "\n Logging failed !!!!" << std::endl;
			return;
		}

		if (last_brace_pos != std::string::npos && last_brace_pos > lines_start_pos)
		{
			updated_content = part_before_insertion.substr(0, last_brace_pos + 1) +
				"," + new_log_block + "\n\t\t" + part_after_insertion;
		}
		else {
			size_t lines_array_start = file_content.find('[', lines_start_pos);

			if (lines_array_start != std::string::npos && lines_array_start + 1 == closing_bracket_pos)
			{

				std::string part_before_array_start = file_content.substr(0, lines_array_start + 1);
				std::string part_after_array_end = file_content.substr(closing_bracket_pos);
				updated_content = part_before_array_start + new_log_block + "\n\t\t" + part_after_array_end;
			}
		}

		try
		{
			m_logfile << updated_content;
		}
		catch (const std::exception& message)
		{
			std::cout << "Could not write log to database : " << message.what() << std::endl;
		}

		m_logfile.flush();

		std::cout << "The log was written successfully." << std::endl;

		m_logfile.clear();
		m_logfile.seekp(0, std::ios::beg);

		m_dataModel.Logs.push_back(m_itemModel);
	}
}

void LogService::Close()
{
	if (m_logfile.is_open()) {
		m_logfile.close();
		std::cout << "The log file was successfully closed." << std::endl;
	}
}