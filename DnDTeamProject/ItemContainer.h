#pragma once
#include <vector>
#include "Item.h"

class ItemContainer {

	public:
		ItemContainer();
		ItemContainer(int capacity);
		~ItemContainer();


		std::vector<Item*> getContents();
		int getCapacity();
		int getQuantity();


		void setCapacity(int capacity);
		void setQuantity(int quantity);


		Item* withdrawItem(Item& item);
		Item* withdrawItem(int index);
		void depositItem(Item& item);

		std::string toString();

	private:

		std::vector<Item*> _contents;
		int _capacity;
		int _quantity;

};