#pragma once
#include <map>
#include "Item.h"

class Inventory
{
private:
	struct ItemPointerCompare{
		bool operator()(const Item* a, const Item* b) const {
			return a->GetName() < b->GetName();
		}
	};
	std::map<const Item*,int, ItemPointerCompare> items;

public:

	void RemoveItem(const Item* item);

	void AddItem(const Item* item);

	const Item* GetRandomItem()const;

	

};

