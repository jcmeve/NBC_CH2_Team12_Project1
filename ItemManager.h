#pragma once
#include <string>
#include <map>
#include <vector>
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
    std::vector<Item*> allItems;
public:
    void Init();
    const Item* GetUsableItem(std::wstring name);
    const Item* GetArtifact(std::wstring name);
    const Item* GetEquipment(std::wstring name);
    std::vector<Item*>  GetAllItems();

	int GetTotalItemCount() const;
};

