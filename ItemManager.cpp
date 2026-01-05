#include "ItemManager.h"
#include "GameManager.h"
#include "UsableItem.h"
#include "Equipment.h"
#include "Artifact.h"
#include "Enums.h"
#include <vector>

ItemManager::ItemManager() {


}

void ItemManager::Init() {
	std::vector<std::vector<std::wstring>> tokens;
	std::wstring name;
	int gold;
	std::wstring desc;
	int turn;
	std::vector<std::pair<STATS, int>> effects;

	GM::GetSave().LoadItems(L"Usable", tokens);
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
		usables[name] = new UsableItem(name, gold, desc, turn, effects);
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
		//에너지바,15,MADE IN 2024,2,HP 20,ATK 0,DEF 0
		artifacts[name] = new Artifact(name, gold, desc, effects);
	}


	GM::GetSave().LoadItems(L"Equipment", tokens);
	for (auto line : tokens) {
		name = line[0];
		gold = std::stoi(line[1]);
		desc = line[2];

		for (int i = 3; i < line.size(); ++i) {
			size_t idx = line[i].find(L' ');

			effects.push_back(std::pair<STATS, int>(mapSTATS[line[i].substr(0, idx)], std::stoi(line[i].substr(idx + 1))));
		}
		//에너지바,15,MADE IN 2024,2,HP 20,ATK 0,DEF 0
		equipments[name] = new Equipment(name, gold, desc, effects);
	}


    allItems.reserve(usables.size() + artifacts.size() + equipments.size());
    for (auto pair : usables) {
        allItems.push_back(pair.second);
    }
    for (auto pair : artifacts) {
        allItems.push_back(pair.second);
    }
    for (auto pair : equipments) {
        allItems.push_back(pair.second);
    }

}

const Item* ItemManager::GetUsableItem(std::wstring name) {
	return usables[name];
}

const Item* ItemManager::GetArtifact(std::wstring name) {
	return artifacts[name];
}

const Item* ItemManager::GetEquipment(std::wstring name) {
	return equipments[name];
}

int ItemManager::GetTotalItemCount() const {
	return (int)(usables.size() + equipments.size() + artifacts.size());
}
std::vector<Item*> ItemManager::GetAllItems() {
    return allItems;
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
