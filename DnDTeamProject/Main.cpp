#include <iostream>
#include <fstream>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "Character.h"
#include "CharacterBuilder.h"
#include "ItemBuilder.h"
#include "ItemArchive.h"

int main(int argc, char** argv) {

	CharacterBuilder builder;
	builder.construct();

	//ItemBuilder builder;
	//builder.construct();

	/*
	CharacterBuilder builder;
	builder.construct();
	std::cout << builder.getCharacter()->toString() << std::endl;
	*/
	/*
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

	Character* testChar2 = new Character();

	testChar2->setName("John Cena");
	testChar2->setArmor(new Armor(ArmorType::LEATHER));
	testChar2->setBelt(new Belt());
	testChar2->setBoots(new Boots());
	testChar2->setBracers(new Bracers());
	testChar2->setHelmet(new Helmet());
	testChar2->setRing(new Ring());
	testChar2->setShield(new Shield(ShieldType::HEAVY_SHIELD));
	testChar2->setWeapon(new Weapon(WeaponType::LONGSWORD));
	testChar2->getInventory()->depositItem(*(new Bracers()));
	testChar2->getInventory()->depositItem(*(new Helmet()));
	testChar2->getInventory()->depositItem(*(new Bracers()));
	testChar2->getInventory()->depositItem(*(new Ring()));

	Character* testChar3 = new Character();

	testChar3->setName("Donald Trump");
	testChar3->setArmor(new Armor(ArmorType::LEATHER));
	testChar3->setBelt(new Belt());
	testChar3->setBoots(new Boots());
	testChar3->setBracers(new Bracers());
	testChar3->setHelmet(new Helmet());
	testChar3->setRing(new Ring());
	testChar3->setShield(new Shield(ShieldType::HEAVY_SHIELD));
	testChar3->setWeapon(new Weapon(WeaponType::LONGSWORD));
	testChar3->getInventory()->depositItem(*(new Bracers()));
	testChar3->getInventory()->depositItem(*(new Bracers()));
	testChar3->getInventory()->depositItem(*(new Bracers()));
	testChar3->getInventory()->depositItem(*(new Helmet()));
	*/
	/*
	std::vector<Item*> itemsToSave;
	itemsToSave.push_back(new Weapon(WeaponType::LONGBOW));
	itemsToSave.push_back(new Armor(ArmorType::LEATHER));
	itemsToSave.push_back(new Ring());
	ItemArchive saveArchive(itemsToSave);

	{ //Save data
		std::ofstream outfilestream("itemFile.txt");
		boost::archive::text_oarchive outarchive(outfilestream);
		outarchive << saveArchive;
	}


	ItemArchive loadArchive;

	{ //Load data
		std::ifstream infilestream("itemFile.txt");
		boost::archive::text_iarchive inarchive(infilestream);
		inarchive >> loadArchive;
	}



	for (int i = 0, n = loadArchive.getItemArchive().size(); i < n; ++i) {
		std::cout << loadArchive.getItemArchive()[i]->toString() << std::endl;
	}
	*/
	std::cout << "Enter any key to quit: ";
	getchar();

}