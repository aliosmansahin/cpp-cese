#include "Logger.h"

std::string Logger::logFile = "";
std::tm Logger::localTime = {0};
bool Logger::firstUse = true;

std::string Logger::GetCurTime()
{
    std::time_t now = std::time(nullptr);  // Ge�erli zaman� al
    localtime_s(&localTime, &now);  // Zaman� yerel saate d�n��t�r

    // Zaman� formatlamak i�in stringstream kullan
    std::ostringstream oss;
    oss << (localTime.tm_year + 1900)  // Y�l (1900'dan ba�lar)
        << (localTime.tm_mon + 1)      // Ay (0-11, bu y�zden +1)
        << localTime.tm_mday           // G�n
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
        // �lk kullan�mda log dosyas�n�n ad�n� olu�tur
        std::string t = GetCurTime();
        logFile = "Logs\\" + t + ".log";
        firstUse = false;
    }

    // Dosyay� ekleme modunda a� (append mode)
    std::ofstream logStream(logFile, std::ios::app);

    // Dosya a��lamazsa, hata mesaj� g�ster
    if (!logStream.is_open()) {
        MessageBox(NULL, L"Log file could not be opened", L"ERROR", MB_OK);
        return;
    }

    char buffer[20];  // Zaman damgas�n� almak i�in buffer

    std::time_t now = std::time(nullptr);  // Ge�erli zaman� al
    localtime_s(&localTime, &now);  // Zaman� yerel saate d�n��t�r
    // Zaman damgas�n� al (belirli formatla)
    std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", &localTime);

    // Zaman damgas�n� ve mesaj� dosyaya yaz
    logStream << "[" << buffer << "] " << message << std::endl;

    // Dosyay� kapat (std::ofstream destructor'� otomatik olarak dosyay� kapat�r, ama yine de yazal�m)
    logStream.close();
}