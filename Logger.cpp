#include "Logger.h"
#include <iostream>

Logger::Logger() {
}

void Logger::ErrorLog(const std::wstring& s) const {
    std::wcout << s << std::endl;
    exit(-1);
}
