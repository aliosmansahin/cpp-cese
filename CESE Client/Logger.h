#pragma once

#include <fstream>
#include <Windows.h>
#include <ctime>
#include <sstream>
#include <filesystem>



class Logger
{
public:
	static void Log(const std::string& message);

	Logger() = delete;
private:
	static std::string GetCurTime();
private:
	static std::string logFile;
	static std::tm localTime;
	static bool firstUse;
};


//namespace Logger {
//
//    std::string GetCurTime()
//    {
//        std::time_t now = std::time(nullptr);
//        localtime_s(localTime, &now);
//        std::ostringstream oss;
//        oss << localTime->tm_year + 1900
//            << localTime->tm_mon + 1
//            << localTime->tm_mday
//            << "_"
//            << localTime->tm_hour
//            << localTime->tm_min;
//
//        return oss.str();
//    }
//
//
//    void Log(const std::string& message)
//    {
//        if (firstUse) {
//            logFile = std::string(GetCurTime() + ".log");
//            firstUse = false;
//        }
//
//        // Dosyay� a� (ekleme modunda)
//        std::ofstream logStream(logFile, std::ios::app);
//
//        // E�er dosya a��lamazsa, hata mesaj� g�ster
//        if (!logStream.is_open()) {
//            MessageBox(NULL, L"Log file could not opened", L"ERROR", MB_OK);
//            return;
//        }
//
//        char buffer[20];
//
//        // Zaman damgas� al
//        std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", localTime);
//
//        // Zaman damgas�n� ve mesaj� dosyaya yaz
//        logStream << "[" << buffer << "] " << message << std::endl;
//
//        // Dosyay� kapat
//        logStream.close();
//    }
//}