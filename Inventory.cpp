#include "Inventory.h"
#include "Utilities.h"
	void Inventory::AddItem(const Item* item) 
	{
		items[item]++;
	}

	void Inventory::RemoveItem(const Item* item) 
	{
		auto it = items.find(item);
		if (it != items.end()) {
			--(it->second);
			if (it->second == 0)
				items.erase(it);
		}
		else {
			
		}
	}

	const Item* Inventory::PopRandomItem() 
	{
		if (items.empty())
			return nullptr;

		int idx = Utilities::GenerateRandomValue(0, items.size()-1);
		auto it = std::next(items.begin(), idx);
		auto ret = it->first;
		--(it->second);
		if (it->second == 0)
			items.erase(it);

		return ret;

		
	}

	
		