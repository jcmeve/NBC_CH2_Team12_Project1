#include "Inventory.h"


	void Inventory::addItem(Item* item) 
	{
		items.push_back(item);
	}

	void Inventory::removeItem(Item* item) 
	{
		items.erase(std::remove(items.begin(), items.end(), item), items.end());
	}

