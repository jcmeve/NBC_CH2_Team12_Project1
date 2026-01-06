#pragma once
#include <map>
#include "UsableItem.h"
#include "Equipment.h"
#include "Artifact.h"
#include "Utilities.h"

class Inventory
{
private:

	std::map<const UsableItem*, int, ItemPointerCompare> usableItems;//1
	std::map<const Equipment*, int, ItemPointerCompare> equipments;//2
	std::map<const Artifact*, int, ItemPointerCompare> artifacts;//3
	std::vector<std::pair<const Item*, int>> indeces;
public:

	void RemoveItem(const Item* item);

	void AddItem(const Item* item);
	const std::pair<const Item*,int>* GetItem(int idx);
	const UsableItem* PopRandomUsableItem();

	const std::map<const UsableItem*, int, ItemPointerCompare>& GetUsableItems();
	const std::map<const Equipment*, int, ItemPointerCompare>& GetEquipments();
	const std::map<const Artifact*, int, ItemPointerCompare>& GetArtifacts();
	void UpdateIndeces();

};

