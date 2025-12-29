#pragma once
#include <string>

class Logger {
private:
    Logger();
    Logger& operator=(const Logger& other) = delete;
    Logger(const Logger& other) = delete;
    Logger& operator=(const Logger&& other) = delete;
    Logger(const Logger&& other) = delete;
    friend class GameManager;
public:
    void ErrorLog(const std::wstring& s) const;
};

