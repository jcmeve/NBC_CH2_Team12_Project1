#include "ItemManager.h"
#include "GameManager.h"
#include "Item.h"
#include "Enums.h"
#include <vector>

ItemManager::ItemManager() {


}

void ItemManager::Init() {
    std::vector<std::vector<std::wstring>> tokens;
    GM::GetSave().LoadItems(L"Usable", tokens);
    std::wstring name;
    int gold;
    std::wstring desc;
    int turn;
    std::vector<std::pair<STATS, int>> effects;

    for (auto line : tokens) {
        name = line[0];
        gold = std::stoi(line[1]);
        desc = line[2];
        turn = std::stoi(line[3]);

        for (int i = 4; i < line.size(); ++i) {
            size_t idx = line[i].find(L' ');

            effects.push_back(std::pair<STATS, int>(mapSTATS[line[i].substr(0, idx)], std::stoi(line[i].substr(idx + 1))));
        }
        //에너지바,15,MADE IN 2024,2,HP 20,ATK 0,DEF 0
        usables[name] = new Item(name, gold, desc, turn, effects);

    }

    GM::GetSave().LoadItems(L"Artifact", tokens);
    for (auto line : tokens) { 
        name = line[0];
        gold = std::stoi(line[1]);
        desc = line[2];

        for (int i = 3; i < line.size(); ++i) {
            size_t idx = line[i].find(L' ');
            
            effects.push_back(std::pair<STATS, int>(mapSTATS[line[i].substr(0, idx)], std::stoi(line[i].substr(idx + 1))));
            
        }
        artifacts[name] = new Item(name, gold, desc, effects);
    }
    //artifacts(std::wstring name, int gold, std::wstring desc, std::vector<std::pair<STATS, int>> effects) : Item(name, gold, desc, 0, effects)

    GM::GetSave().LoadItems(L"Equipment", tokens);
    for (auto line : tokens) {
        name = line[0];
        gold = std::stoi(line[1]);
        desc = line[2];

        for (int i = 3; i < line.size(); ++i) {
            size_t idx = line[i].find(L' ');
           
            effects.push_back(std::pair<STATS, int>(mapSTATS[line[i].substr(0, idx)], std::stoi(line[i].substr(idx + 1))));
            
        }
        equipments[name] = new Item(name, gold, desc, effects);
    }
    //equipments(std::wstring name, int gold, std::wstring desc, std::vector<std::pair<STATS, int>> effects) : Item(name, gold, desc, 0, effects)
}
ItemManager::~ItemManager() {
    for (auto& pair : usables)
        delete pair.second;
    for (auto& pair : equipments)
        delete pair.second;
    for (auto& pair : artifacts)
        delete pair.second;

    usables.clear();
    equipments.clear();
    artifacts.clear();
}
