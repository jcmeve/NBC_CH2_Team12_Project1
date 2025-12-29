#pragma once
#include <vector>
#include "Item.h"

class Inventory
{
private:
	std::vector<Item*> items;

public:

	void removeItem(Item* item);

	void addItem(Item* item);

	Item* randomItem();

	

};

