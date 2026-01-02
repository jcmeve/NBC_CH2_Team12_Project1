#include "Logger.h"
#include <iostream>
#include "GameManager.h"
Logger::Logger() {
}

void Logger::ErrorLog(const std::wstring& s) const {
    GM::GetDisplay().WriteString(s);
    exit(-1);
}

void Logger::Log(const std::wstring& s) const {
    GM::GetDisplay().WriteString(s);
}

void Logger::LogSlow(const std::wstring& s, float time) const {
    GM::GetDisplay().WriteStringSlow(s,time)
}
