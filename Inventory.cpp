#include "Inventory.h"
#include "Utilities.h"
	void Inventory::AddItem(const Item* item) 
	{
		auto it = items.find(item);
		if (it != items.end()) {
			++(it->second);
		}
		else {
			items.emplace(item, 1);
		}
	}

	void Inventory::RemoveItem(const Item* item) 
	{
		auto it = items.find(item);
		if (it != items.end()) {
			--(it->second);
			if (it->second == 0)
				items.erase(item);
		}
		else {
			
		}
	}

	const Item* Inventory::GetRandomItem() const
	{
		if (items.empty())
			return nullptr;

		int idx = Utilities::GenerateRandomValue(0, items.size()-1);
		auto it = std::next(items.begin(), idx);
		
		return it->first;

		
	}

	
		