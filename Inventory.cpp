#include "Inventory.h"
#include<iostream>
#include<algorithm>
#include<random>
#include<cstdlib>
#include<ctime>


	void Inventory::addItem(Item* item) 
	{
		items.push_back(item);
	}

	void Inventory::removeItem(Item* item) 
	{
		items.erase(std::remove(items.begin(), items.end(), item), items.end());
	}

	Item* Inventory::randomItem()
	{
		if (items.empty())
		{

		std::cout << "인벤토리가 비어있습니다!" << std::endl;

		return nullptr;

		}

		else 
		{
			std::srand(static_cast<unsigned int>(std::time(0)));

			int randomIndex = std::rand() % items.size();

			Item* randomItem = items[randomIndex];

			items.erase(items.begin() + randomIndex);

			return randomItem;

		}
		
	}

	
		