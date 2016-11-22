#include <fstream>
#include "Item.h"
#include "ItemContainer.h"
#include "Weapon.h"
#include "Equipment.h"
#include "Character.h"
#include "Map.h"


int main(int argc, char** argv) {

	/*
	std::vector<Enchant*> enchants{ &Enchant(Stats::ATK, 5) };
	Item testItem("Halberd", ItemType::WEAPON, enchants);

	ItemContainer testContainer;
	testContainer.addItem(&testItem);

	Character testFighter("Wilfred Abbernathy", "Fighter", 1, 10, 10, 10, 10, 10, 10);
	*/

	std::cout << "Test" << std::endl;

	Map m1 = Map(5, 5);
	
	m1.setCell(2, 2, '#');
	//m1.setCell(2, 1, '#');
	m1.setCell(2, 3, '#');

	m1.displayGrid();

	system("PAUSE");
	
	if (m1.validateA())
		std::cout << "Valid map." << std::endl;
	else
		std::cout << "Invalid Map" << std::endl;
		

	//m1.printCellNeighbors(3, 3);

	system("PAUSE");


}