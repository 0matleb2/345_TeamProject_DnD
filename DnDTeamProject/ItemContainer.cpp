//! @file
//! @brief Implementation file for Item Container class
//!
#include "ItemContainer.h"

//! default constructor
ItemContainer::ItemContainer()
{

}

//! copy constructor
//! @param orig : original container to be copied
ItemContainer::ItemContainer(const ItemContainer& orig)
{
	int s = orig.contents.size();
	// iterate through vector of original, clone and push into new vector.
	for (int i = 0; i < s; i++)
	{
		contents.push_back(orig.contents[i]->clone());
	}
}

//! retrieve item by index.
//! @param pos : index of Item to retrieve
//! @return : desired Item
Item* ItemContainer::getItem(int pos)
{
	return contents[pos];
}

//! add Item to container
//! @param i : Item to add
void ItemContainer::addItem(Item* i)
{
	contents.push_back(i);
}

//! remove Item from container
//! @param : index of Item to remove
//! @return : removed Item
Item* ItemContainer::removeItem(int pos)
{

	Item* it = contents[pos];

	contents.erase(contents.begin() + pos);

	return it;

}

//! method prints contents of the Container
//! (probably should have just overloaded << in retrospect)
void ItemContainer::printContents()
{
	cout << "Contents of Container (" << contents.size() << " items):" << endl;
	int indexno = 0;

	for (int it = 0; it < contents.size(); it++)
	{
		cout << indexno << ") ";
		contents[it]->print();
		indexno++;
	}

	cout << endl;
}

//! returns number of items in Container
//! @return : no. of Items in Container
int ItemContainer::getSize()
{
	return contents.size();
}

//! returns the index of an item, if it is present in the ItemContainer, that is
//! @return: index of item in vector, returns -1 if there is none to be found
int ItemContainer::getItemIndex(Item* it) {
	//this will give the index of the item, if there is any
	int pos = std::find(contents.begin(), contents.end(), it) - contents.begin();
	//making sure the integer isn't out of bounds. If it is, it could not be found
	//-1 means "doesn't have item"
	if (pos >= contents.size())
		return -1;
	else return pos;
}

void ItemContainer::rescale(int tgt_lvl)
{
	if (contents.size() == 0)
		return;

	for (int i = 0; i < contents.size(); i++)
	{
		contents[i]->rescale(tgt_lvl);
	}
}

//! destructor
ItemContainer::~ItemContainer()
{
	for (int it = 0; it < contents.size(); it++)
	{
		//iterate through vector and delete all pointers

		delete contents[it];

	}
	contents.clear();
}