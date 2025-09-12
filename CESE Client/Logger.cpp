#include "Logger.h"

std::string Logger::logFile = "";
std::tm Logger::localTime = {0};
bool Logger::firstUse = true;

std::string Logger::GetCurTime()
{
    std::time_t now = std::time(nullptr);  // Geçerli zamaný al
    localtime_s(&localTime, &now);  // Zamaný yerel saate dönüþtür

    // Zamaný formatlamak için stringstream kullan
    std::ostringstream oss;
    oss << (localTime.tm_year + 1900)  // Yýl (1900'dan baþlar)
        << (localTime.tm_mon + 1)      // Ay (0-11, bu yüzden +1)
        << localTime.tm_mday           // Gün
        << "_"
        << localTime.tm_hour           // Saat
        << localTime.tm_min
        << localTime.tm_sec;

    return oss.str();
}

void Logger::Log(const std::string& message)
{
    if (firstUse) {
        
        std::filesystem::create_directory("Logs");
        // Ýlk kullanýmda log dosyasýnýn adýný oluþtur
        std::string t = GetCurTime();
        logFile = "Logs\\" + t + ".log";
        firstUse = false;
    }

    // Dosyayý ekleme modunda aç (append mode)
    std::ofstream logStream(logFile, std::ios::app);

    // Dosya açýlamazsa, hata mesajý göster
    if (!logStream.is_open()) {
        MessageBox(NULL, L"Log file could not be opened", L"ERROR", MB_OK);
        return;
    }

    char buffer[20];  // Zaman damgasýný almak için buffer

    std::time_t now = std::time(nullptr);  // Geçerli zamaný al
    localtime_s(&localTime, &now);  // Zamaný yerel saate dönüþtür
    // Zaman damgasýný al (belirli formatla)
    std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", &localTime);

    // Zaman damgasýný ve mesajý dosyaya yaz
    logStream << "[" << buffer << "] " << message << std::endl;

    // Dosyayý kapat (std::ofstream destructor'ý otomatik olarak dosyayý kapatýr, ama yine de yazalým)
    logStream.close();
}