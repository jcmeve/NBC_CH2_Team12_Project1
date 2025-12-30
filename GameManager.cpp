#include "GameManager.h"
#include "Logger.h"
#include "DisplayManager.h"
#include "Actor.h"
#include <algorithm>
#include <atomic>
#include <chrono>
GameManager::GameManager():display(200, 70),logger(),input(),isEngineEnd(false){
    system("cls");
}
void GameManager::RemoveActor(Actor* actor) {
    std::vector<Actor*>& actors = GetInstance().actors;
    auto it = std::find(actors.begin(), actors.end(), actor);

    if (it != actors.end()) {
        std::iter_swap(it, actors.end() - 1);
        delete actor;
        actors.pop_back();
    }
   
}
void GameManager::Tick(float deltaTime) {
    std::vector<Actor*> actors = GetInstance().actors;
    for (Actor* actor : actors) {
        actor->Tick(deltaTime);
    }
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
    std::vector<Actor*>& actors = GetInstance().actors;
    for (Actor* actor : actors) {
        delete actor;
    }
    actors.clear();

    return true;
}
 
void GameManager::DestroyActor(Actor* actor) {
    if (!actor) return;
    GetInstance().garbageActors.push_back(actor);
}

void GameManager::Loop() {
    static std::atomic_char cnt = 0;
    ++cnt;
    _ASSERT(cnt == 1);
    GameManager& gm = GetInstance();

    std::vector<Actor*>& garbageActors = gm.garbageActors;
    std::vector<Actor*>& actors = gm.actors;
    while (!gm.isEngineEnd) {
        for (Actor* actor : actors) {
            actor->Tick(deltaTime);
        }
     
        //Demand Destroy
        for (Actor* actor : garbageActors) {
            RemoveActor(actor);
        }
        garbageActors.clear();
    }
}
