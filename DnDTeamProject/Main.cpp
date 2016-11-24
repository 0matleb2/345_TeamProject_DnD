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
	m1.setCell(2, 1, '#');
	//m1.setCell(2, 3, '#');

	m1.displayGrid();

	system("PAUSE");
	
	std::vector<Map::SearchCell*> pathA = m1.findPath(m1.getEntry(), m1.getExit());

	m1.printPath(&pathA);

	std::cout << "Valid? :" << m1.validateA() << std::endl;

	//bool checkR = m1.inRange(m1.getCell(1, 1), m1.getCell(3, 1), 2);

	//std::cout << checkR << std::endl;
	
	//Map::Cell* c1 = m1.nextMove(m1.getEntry(), m1.getExit());

	//std::cout << "Next move: x -" << c1->getX() << " , y-" << c1->getY() << std::endl;

	//m1.printCellNeighbors(3, 3);

	system("PAUSE");


}