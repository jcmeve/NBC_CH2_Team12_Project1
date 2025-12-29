#pragma once
#include "Logger.h";
#include "DisplayManager.h";
typedef GameManager GM;
class GameManager {
    DisplayManager display;
    Logger logger;
    
private:
    GameManager();
    GameManager& operator=(const GameManager& other) = delete;
    GameManager(const GameManager& other) = delete;
    GameManager& operator=(const GameManager&& other) = delete;
    GameManager(const GameManager&& other) = delete;
public:
    static Logger& GetLogger();
    static DisplayManager& GetDisplay();
    static GameManager& GetInstance();
    
};

