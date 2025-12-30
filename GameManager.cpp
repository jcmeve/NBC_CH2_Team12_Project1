#include "GameManager.h"
#include "Logger.h"
#include "DisplayManager.h"

GameManager::GameManager():display(200, 70),logger(),input(),isEngineEnd(false){
    system("cls");
}
Logger& GameManager::GetLogger() {
    return GetInstance().logger;
}

DisplayManager& GameManager::GetDisplay() {
    return GetInstance().display;
}

InputManager& GameManager::GetInput() {
    return GetInstance().input;
}

GameManager& GameManager::GetInstance() {
    static GameManager instance;
    return instance;
}

bool GameManager::IsEnd() {
    return GetInstance().isEngineEnd;
}

bool GameManager::ShutDown() {
    GetInstance().isEngineEnd = true;

    return true;
}
