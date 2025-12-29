#include "GameManager.h"
#include "Logger.h"
#include "DisplayManager.h"

GameManager::GameManager():display(200, 70),logger(){
    system("cls");
}
Logger& GameManager::GetLogger() {
    return GetInstance().logger;
}

DisplayManager& GameManager::GetDisplay() {
    return GetInstance().display;
}

GameManager& GameManager::GetInstance() {
    static GameManager instance;
    return instance;
    // TODO: 여기에 return 문을 삽입합니다.
}
