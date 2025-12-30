#pragma once
#include "Logger.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include <vector>
#include <memory>
class GameManager {
    DisplayManager display;
    Logger logger;
    InputManager input;
    bool isEngineEnd;
    std::vector<Actor*> actors;
    std::vector<Actor*> garbageActors;
private:
    GameManager();
    GameManager& operator=(const GameManager& other) = delete;
    GameManager(const GameManager& other) = delete;
    GameManager& operator=(const GameManager&& other) = delete;
    GameManager(const GameManager&& other) = delete;
    static void RemoveActor(Actor* actor);
public:
    static Logger& GetLogger();
    static DisplayManager& GetDisplay();
    static InputManager& GetInput();
    static GameManager& GetInstance();
    static bool IsEnd();
    static bool ShutDown();
    template<typename T, typename = typename std::enable_if<std::is_base_of<Actor, T>::value>::type>
    static T* CreateActor() {
        T* temp = new T();
        GetInstance().actors.push_back(temp);
        return temp;
    }
    static void DestroyActor(Actor* actor);
    static void Tick(float deltaTime) ;

}typedef GM;


