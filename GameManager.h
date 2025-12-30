#pragma once
#include "Logger.h"
#include "DisplayManager.h"
#include "InputManager.h"
class GameManager {
    DisplayManager display;
    Logger logger;
    InputManager input;
    bool isEngineEnd;
private:
    GameManager();
    GameManager& operator=(const GameManager& other) = delete;
    GameManager(const GameManager& other) = delete;
    GameManager& operator=(const GameManager&& other) = delete;
    GameManager(const GameManager&& other) = delete;
public:
    static Logger& GetLogger();
    static DisplayManager& GetDisplay();
    static InputManager& GetInput();
    static GameManager& GetInstance();
    static bool IsEnd();
    static bool ShutDown();
    
}typedef GM;


