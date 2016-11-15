#include <fstream>
#include "Item.h"
#include "ItemContainer.h"
#include "Weapon.h"
#include "Equipment.h"
#include "Character.h"


int main(int argc, char** argv) {

	std::vector<Enchant*> enchants{ &Enchant(Stat::ATK, 5) };
	Item testItem("Halberd", ItemType::WEAPON, enchants);

	ItemContainer testContainer;
	testContainer.addItem(&testItem);

	Character testFighter("Wilfred Abbernathy", "Fighter", 1, 10, 10, 10, 10, 10, 10);







}