#pragma once
#include <string>
#include <map>
class Item;
class ItemManager {
private:
    ItemManager();
    ~ItemManager();
    ItemManager& operator=(const ItemManager& other) = delete;
    ItemManager(const ItemManager& other) = delete;
    ItemManager& operator=(const ItemManager&& other) = delete;
    ItemManager(const ItemManager&& other) = delete;
    friend class GameManager;
    std::map<std::wstring, Item*> usables;
    std::map<std::wstring, Item*> equipments;
    std::map<std::wstring, Item*> artifacts;
public:
    void Init();
    Item CreateItem(std::wstring name);
    Item CreateArtifact(std::wstring name);
    Item CreateEquipment(std::wstring name);

};

