#include "ItemManager.h"
#include "GameManager.h"
#include <vector>

ItemManager::ItemManager() {
    std::vector<std::vector<std::wstring>> tokens;
    GM::GetSave().LoadItems(L"Usable", tokens);
    GM::GetSave().LoadItems(L"Artifact", tokens);
    GM::GetSave().LoadItems(L"Equipment", tokens);
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
