#include "Inventory.h"
#include "Utilities.h"
	void Inventory::AddItem(const Item* item) 
	{
		
		if (const UsableItem* usable = dynamic_cast<UsableItem*>(const_cast<Item*>(item))){
			usableItems[usable]++;
		}
		else if (const Equipment* usable = dynamic_cast<Equipment*>(const_cast<Item*>(item))) {
			equipments[usable]++;
		}
		else if (const Artifact* usable = dynamic_cast<Artifact*>(const_cast<Item*>(item))) {
			artifacts[usable]++;
		}
		UpdateIndeces();

	}

	const std::pair<const Item*,int>* Inventory::GetItem(int idx) {
		if (idx >= indeces.size())
			return nullptr;
		return &indeces[idx];
	}

	void Inventory::RemoveItem(const Item* item) 
	{
		if (const UsableItem * usable = dynamic_cast<const UsableItem*>(item)) {
			auto it = usableItems.find(usable);
			if (it != usableItems.end()) {
				--(it->second);
				if (it->second == 0)
					usableItems.erase(it);
			}
		}else if (const Equipment* equip = dynamic_cast<const Equipment*>(item)) {
			auto it = equipments.find(equip);
			if (it != equipments.end()) {
				--(it->second);
				if (it->second == 0)
					equipments.erase(it);
			}
		}else if (const Artifact* artifact = dynamic_cast<const Artifact*>(item)) {
			auto it = artifacts.find(artifact);
			if (it != artifacts.end()) {
				--(it->second);
				if (it->second == 0)
					artifacts.erase(it);
			}
		}
		UpdateIndeces();



	}

	const UsableItem* Inventory::PopRandomUsableItem()
	{
		if (usableItems.empty())
			return nullptr;

		int idx = Utilities::GenerateRandomValue(0, usableItems.size()-1);
		auto it = std::next(usableItems.begin(), idx);
		auto ret = it->first;
		--(it->second);
		if (it->second == 0)
			usableItems.erase(it);
		UpdateIndeces();
		return ret;

		
	}

	const std::map<const UsableItem*, int, ItemPointerCompare>& Inventory::GetUsableItems() {
		return usableItems;
	}

	const std::map<const Equipment*, int, ItemPointerCompare>& Inventory::GetEquipments() {
		return equipments;
	}

	const std::map<const Artifact*, int, ItemPointerCompare>& Inventory::GetArtifacts() {
		return artifacts;
	}

	void Inventory::UpdateIndeces() {

		indeces.clear();
		for (auto& pair : usableItems) indeces.push_back({ pair.first, pair.second });
		for (auto& pair : equipments)  indeces.push_back({ pair.first, pair.second });
		for (auto& pair : artifacts)   indeces.push_back({ pair.first, pair.second });
		
	}

