#pragma once
#include "Logger.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include <vector>
#include <memory>
class GameManager {
    DisplayManager display;
    Logger logger;
    InputManager input;
    SoundManager sound;
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
    static SoundManager& GetSound();
    static GameManager& GetInstance();
    static bool IsEnd();
    static bool ShutDown();
    
    template<typename T, typename = typename std::enable_if<std::is_base_of<Actor, T>::value>::type>
    static T* CreateActor(const std::wstring& name) {
        T* temp = new T(name);
        GetInstance().actors.push_back(temp);
        return temp;
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Actor, T>::value>::type>
    static T* CreateActor() {
        return CreateActor<T>(std::wstring(L"NONAME"));
    }

    static void DestroyActor(Actor* actor);
    static void Tick(float deltaTime) ;

}typedef GM;


