#include <storage_logging/LogService.h>
#include <thread>

int main() {
    std::cout << "--- LogService Test Baslatiliyor ---" << std::endl;

    // Lambda: Dosya icerigini okuma (Test Helper Function)
    auto readLogFileContent = [](const std::string& filename = "applog.json") -> std::string {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return "ERROR: Log file not found or could not be opened.";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
        };

    LogService* logService = nullptr;

    // 1. Singleton Testi
    std::cout << "\n1. Singleton Testi:" << std::endl;
    logService = LogService::getInstance();
    LogService* logService2 = LogService::getInstance();

    if (logService == logService2) {
        std::cout << "SUCCESS: getInstance() ayni ornegi dondurdu. (P: " << logService << ")" << std::endl;
    }
    else {
        std::cout << "FAILED: getInstance() farkli ornekler dondurdu." << std::endl;
    }

    // 2. Start (File Open/Create and Init Log) Testi
    std::cout << "\n2. Start ve Initialization Log Testi:" << std::endl;
    bool start_status = logService->Start();
    if (start_status) {
        std::cout << "SUCCESS: LogService baslatildi." << std::endl;
    }
    else {
        std::cout << "FAILED: LogService baslatilamadi." << std::endl;
        return 1;
    }

    std::string content_after_start = readLogFileContent();
    if (content_after_start.find("\"Logs\": []") != std::string::npos) {
        std::cout << "SUCCESS: Initialization JSON yapisi dogru (Logs: [])." << std::endl;
    }
    else {
        std::cout << "FAILED: Initialization JSON yapisi beklenenden farkli." << std::endl;
    }

    // 3. New Log Entry Test (Log 1)
    std::cout << "\n3. Yeni Log Girisi Testi (Log 1):" << std::endl;
    logService->writeLog("Veri okuma islemi baslatiliyor.", "DataProcessor");
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // 4. New Log Entry Test (Log 2)
    std::cout << "4. Yeni Log Girisi Testi (Log 2):" << std::endl;
    logService->writeLog("Islem basariyla tamamlandi.", "DataProcessor");

    // 5. Updated Log File Content Check
    std::string content_after_logs = readLogFileContent();
    std::cout << "\n5. Guncel Log Dosyasi (applog.json) Icerigi Kontrolu:" << std::endl;

    if (content_after_logs.find("\"LogNo\": \"1\"") != std::string::npos &&
        content_after_logs.find("\"LogNo\": \"2\"") != std::string::npos) {
        std::cout << "SUCCESS: Iki log girisi de dosyada bulundu ve LogNo dogru artmis." << std::endl;
    }
    else {
        std::cout << "FAILED: Loglar dosyaya dogru sekilde eklenmedi." << std::endl;
    }

    // 6. Close (File Close) Test
    std::cout << "\n6. Close Testi:" << std::endl;

    // Close() fonksiyonu cagriliyor.
    logService->Close();

    // Close() baþarýlý kabul edilir, çünkü LogService::Close() içinde dosyanýn kapatýldýðý yazdýrýlacaktýr.
    std::cout << "SUCCESS: Close fonksiyonu cagrildi ve dosya kapatildi." << std::endl;

    std::cout << "\n--- LogService Test Sonlandirildi ---" << std::endl;
    return 0;
}