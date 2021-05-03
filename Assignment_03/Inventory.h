#pragma once

#include <iostream>
#include "Item.h"

class Inventory
{
public:
	//COMMENT: Use the initialization list more often.
	Inventory()
	{
		//TODO: Implement a default constructor for the Inventory class where the max number of slots
		// is 5 and all the slots are free (They are not occupied).
		mMaxSlots = 5;
		mInventory = new Item[mMaxSlots];
		mSlotsOccupied = 0;
	}
	//COMMENT: Initialization list for mSlotsOccupied.
	Inventory(uint32_t capacity) : mMaxSlots(capacity)
	{
		//TODO: Implement a non default constructor for the Inventory class where 
		//all the slots are free (They are not occupied).
		mInventory = new Item[capacity];
		mSlotsOccupied = 0;
	}
	
	//COMMENT: You don't need to loop through the mMaxSlots. You just want to copy mSlotsOccupied. What is not 
	//occupied you should not care.
	Inventory(const Inventory& other)
	{
		//TODO: Implement a copy constructor for this class. Avoid shallow copy.
		mMaxSlots = other.mMaxSlots;

		mInventory = new Item[mMaxSlots];
		for (int i = 0; i < mMaxSlots; i++)
		{
			mInventory[i] = other.mInventory[i];
		}

		mSlotsOccupied = other.mSlotsOccupied;		
	}

	//ERROR: -1. other.mMaxSlots should go to a state that does not make sense, like for example: 0
	Inventory(Inventory&& other) noexcept
	{
		//TODO: Implement a move constructor for this class. Reset to a default state the other inventory.
		mMaxSlots = other.mMaxSlots;
		mInventory = other.mInventory;
		mSlotsOccupied = other.mSlotsOccupied;

		other.mMaxSlots = 5;
		mInventory = new Item[other.mMaxSlots];
		mSlotsOccupied = 0;
	}

	//ERROR: -2. You forgot to set mInventory = nullptr. Without this, you will have dangling pointers.
	~Inventory()
	{
		//TODO: Implement a destructor for this class.
		delete[] mInventory;
	}

	//ERROR: -2. You should check first if they are equal and just copy otherwise.
	//TODO: Implement a copy assignment operator
	Inventory& operator=(const Inventory& other)
	{
		mMaxSlots = other.mMaxSlots;

		mInventory = new Item[mMaxSlots];
		for (int i = 0; i < mMaxSlots; i++)
		{
			mInventory[i] = other.mInventory[i];
		}

		mSlotsOccupied = other.mSlotsOccupied;

		return *this;
	}

	//ERROR: -2. You should check first if they are equal and just move otherwise.
	//Also, make other.mMaxSlots to receive an empty state(An number that doesn't make sense).
	//TODO: Implement a move assignment operator
	Inventory& operator=(Inventory&& other) noexcept
	{
		mMaxSlots = other.mMaxSlots;

		if (mInventory != nullptr)
		{
			delete[] mInventory;
		}

		mInventory = other.mInventory;
		mSlotsOccupied = other.mSlotsOccupied;

		other.mMaxSlots = 5;
		mInventory = new Item[other.mMaxSlots];
		mSlotsOccupied = 0;

		return *this;
	}

	//COMMENT: Remove commented code in order to improve redability.
	//ERROR: -2. The addItem works fine but does not deals with special case.
	//Check the commented code below.
	//void AddItem(Item newItem)
	//{
	//	if (!isFullForItem(&newItem))
	//	{
	//		int slotIndex = SearchItemByNameLessThan50(newItem.name);
	//		//I have this Item in inventory
	//		if (slotIndex != -1)
	//		{
	//			int futureQuantity = mInventory[slotIndex].quantity + newItem.quantity;
	//			if (futureQuantity > 50)
	//			{
	//				newItem.quantity = futureQuantity - 50;
	//				mInventory[slotIndex].quantity = 50;
	//				mInventory[mSlotsOccupied] = newItem;
	//				mSlotsOccupied++;
	//				return;
	//			}

	//			mInventory[slotIndex].quantity += newItem.quantity;
	//			return;
	//		}
	//		//Inserting for the first time
	//		else
	//		{
	//			//Expanding inventory;
	//			if ((newItem.type == ItemType::Charm) && (newItem.name.compare("Expansion") == 0))
	//			{
	//				Item* temp = mInventory;
	//				mMaxSlots += 5;
	//				mInventory = new Item[mMaxSlots];
	//				for (int i = 0; i < mSlotsOccupied; ++i)
	//				{
	//					mInventory[i] = temp[i];
	//				}
	//				delete[] temp;
	//				temp = nullptr;
	//			}

	//			//After expansion, insert.
	//			mInventory[mSlotsOccupied] = newItem;
	//			mSlotsOccupied++;
	//		}
	//	}
	//	std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
	//}


	void AddItem(Item newItem)
	{
		//TODO: Implement AddItem Method. This method adds a new item to the inventory. 
		//First it searches for this item to see if the item exists, and if the item exists 
		//it checks the quantity, because the max quantity allowed per slot is 50.
		//So, for example, if you have 50 healing potions in your inventory, and you want to add one more, this potion
		//should occupy a new slot. Pay attention that the SearchItem function already does this quantity check for you.
		//The extra check that you should do is for the accumulated quantity. So your function should check
		//how many items this current slot has and if you add this new item quantity, how many items you will have.
		//If it's greater than 50, you should make the quantity of one slot 50 and add the remainder quantity to a new slot.
		//For example:
		//[ HP 48 ] [  ] [  ] [  ] [  ] Inventory has a HP(healing potions) with 48 as quantity and you want to add more 5 HP
		//[ HP 50 ] [HP 3] [  ] [  ] [  ] Inventory after you added 5 HP

		//If the Inventory is full, return a message to the user that the inventory is full and the items will be discarted.
		//Use the method IsFullForItem;

		//If after you insert the item your inventory becomes full for the remainder, Print a message to the user with how many
		//items will be discarted;

		//SPECIAL CASE: If the user adds an item of type charm with the name "Expansion" your inventory
		//should expand adding 5 more empty slots for the user.

		int index = SearchItemByName(newItem.name);
		
		if (isFullForItem(&newItem))
		{
			std::cout << "The inventory is full. Item will be discarded!" << std::endl;
			return;
		}

		//if (newItem.type == ItemType::Charm && newItem.name == "Expansion")
		//{
		//	int newMaxSlots = mMaxSlots + 5;

		//	Item* tempInventory = new Item[newMaxSlots];
		//	tempInventory = mInventory;

		//	for (int i = 0; i < mMaxSlots; ++i)
		//	{
		//		tempInventory[i] = mInventory[i];
		//	}
		//	
		//	delete[] mInventory;

		//	mInventory = tempInventory;
		//	mMaxSlots = newMaxSlots;

		//	for (int i = 0; i < mMaxSlots; ++i)
		//	{
		//		mInventory[i] = tempInventory[i];
		//	}
		//	return;
		//}

		if (index != -1)
		{
			int sum = mInventory[index].quantity + newItem.quantity;
			
			if (sum > 50)
			{
				int remainder = sum % 50;
				mInventory[index].quantity = 50;
				
				if (mSlotsOccupied >= mMaxSlots)
				{
					std::cout << "The inventory is full!" << std::endl;

					if (remainder > 0)
					{
						std::cout << remainder << "will be discarded." << std::endl;
					}
				}
				else
				{
					mInventory[mSlotsOccupied] = newItem;
					mInventory[mSlotsOccupied].quantity = remainder;
					mSlotsOccupied++;
					std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
				}
			}
			else
			{
				mInventory[index].quantity += newItem.quantity;
				std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
			}
		}
		else
		{
			mInventory[mSlotsOccupied] = newItem;
			mSlotsOccupied++;
			std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
		}

	}

	void RemoveItem(std::string itemName, int quantity)
	{
		//TODO: Implement RemoveItem method
		//RemoveItem, should remove a quantity from the slot with the item. If the whole slot 
		//is empty, you should shift all the other items of the inventory;
		//If you try to remove more than what you have in one slot, just make the slot empty.
		//For example:
		//[ HP 50 ] [ HP 30 ] [  ] [  ] [  ] //You tried to remove 80 HP from the inventory
		//[ HP 30 ] [  ] [  ] [  ] [  ] //You just remove from one slot.

		int index = SearchItemByName(itemName);

		if (index != -1)
		{
			int result = mInventory[index].quantity - quantity;
			mInventory[index].quantity = result;

			if (result <= 0)
			{
				for (int i = index; i < mSlotsOccupied - 1; ++i)
				{
					mInventory[i] = mInventory[i + 1];
				}
				mSlotsOccupied--;
			}
		}

		std::cout << "Removing " << quantity << " " << itemName << " from inventory." << "\n";

		//SPECIAL CASE: If the user removes the charm Expansion from the inventory, your inventory 
		//should reduce the number of slots in 5, discarting all the items from the removed slots.
	}

	Item* UseItem(std::string itemName)
	{
		// TODO: Search for the item and if it exists, return this item and remove one from the inventory
		// otherwise, return nullptr.
		// The user is just allowed to use the Types: Posion and Utility.

		int index = SearchItemByName(itemName);

		if (index != -1 && (mInventory[index].type == ItemType::Utility || mInventory[index].type == ItemType::Potion))
		{
			Item* newItem = new Item(mInventory[index]); 
			RemoveItem(itemName, 1);
			std::cout << "Using " << itemName << "\n";
			return newItem;
		}
		else
		{
			return nullptr;
		}

	}
private:
	//Array of Items
	Item* mInventory;
	//This variable tracks the capacity of the inventory
	uint32_t mMaxSlots;
	//This variable tracks how many slots are occupied.
	uint32_t mSlotsOccupied;


	//This method searches for the item inside the Inventory and if it finds the item with less than
	//50 as quantity, it returns the index of the item inside the inventory array, otherwise, returns -1.
	int SearchItemByNameLessThan50(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0 && mInventory[i].quantity < 50)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	//Returns the index of the item if it exists and -1 if it doesn't.
	int SearchItemByName(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	//If you don't have the item inside the inventory and all the slots are occupied - True
	//If you have the item in the inventory with max capacity and all the other slots are occupied - True
	//Otherwise - False.
	bool isFullForItem(Item* item) const
	{
		int index = SearchItemByNameLessThan50((*item).name);
		if (index == -1 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		if (index != -1 && mInventory[index].quantity >= 50 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		return false;
	}
};
