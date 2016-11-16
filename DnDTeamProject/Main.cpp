#include <iostream>
#include "Character.h"

int main(int argc, char** argv) {


	Character* testChar = new Character();

	testChar->setName("Bert Mackelin");
	testChar->setArmor(new Armor(ArmorType::LEATHER));
	testChar->setBelt(new Belt());
	testChar->setBoots(new Boots());
	testChar->setBracers(new Bracers());
	testChar->setHelmet(new Helmet());
	testChar->setRing(new Ring());
	testChar->setShield(new Shield(ShieldType::HEAVY_SHIELD));
	testChar->setWeapon(new Weapon(WeaponType::LONGSWORD));
	testChar->getInventory()->depositItem(*(new Ring()));
	testChar->getInventory()->depositItem(*(new Ring()));
	testChar->getInventory()->depositItem(*(new Ring()));
	testChar->getInventory()->depositItem(*(new Ring()));


	std::cout << testChar->toString() << std::endl;

	testChar->getInventory()->withdrawItem(2);

	std::cout << testChar->toString() << std::endl;


	getchar();





}