#pragma once
#include <map>
#include "Item.h"
#include "Utilities.h"

class Inventory
{
private:

	std::map<const Item*,int, ItemPointerCompare> items;

public:

	void RemoveItem(const Item* item);

	void AddItem(const Item* item);

	const Item* PopRandomItem();

	const std::map<const Item*, int, ItemPointerCompare> GetAllItems();

};

