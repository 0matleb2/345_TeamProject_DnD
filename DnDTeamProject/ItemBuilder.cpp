#include <iostream>
#include "ItemBuilder.h"
#include "Menu.h"
#include "Armor.h"
#include "Belt.h"
#include "Boots.h"
#include "Bracers.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
#include "Names.h"
#include "Dice.h"
#include "FileIO.h"


ItemBuilder::ItemBuilder() {
}


ItemBuilder::~ItemBuilder() {
}

Item * ItemBuilder::getItem() {
	return _item;
}

void ItemBuilder::setItem(Item * item) {
	_item = item;
}

void ItemBuilder::construct() {
	std::cout << "Creating a new item..." << std::endl << std::endl;
	std::cout << "What type of item do you want to create?" << std::endl;
	switch (menu(itemBuilderTypeOptions)) {
	case 1:
		buildArmor();
		break;
	case 2:
		buildBelt();
		break;
	case 3:
		buildBoots();
		break;
	case 4:
		buildBracers();
		break;
	case 5:
		buildHelmet();
		break;
	case 6:
		buildRing();
		break;
	case 7:
		buildShield();
		break;
	case 8:
		buildWeapon();
		break;
	}
	saveItem(_item);
}

void ItemBuilder::buildType() {

}

void ItemBuilder::buildIdentity() {
}


void ItemBuilder::buildArmor() {
	//Build armor type
	Armor* armor = &Armor();
	std::cout << "What type of armor do you want to create?" << std::endl;
	switch (menu(itemBuilderArmorTypeOptions)) {
	case 1:
		armor = new Armor(ArmorType::PADDED);
		break;
	case 2:
		armor = new Armor(ArmorType::LEATHER);
		break;
	case 3:
		armor = new Armor(ArmorType::STUDDED_LEATHER);
		break;
	case 4:
		armor = new Armor(ArmorType::CHAIN_SHIRT);
		break;
	case 5:
		armor = new Armor(ArmorType::BREASTPLATE);
		break;
	case 6:
		armor = new Armor(ArmorType::BANDED_MAIL);
		break;
	case 7:
		armor = new Armor(ArmorType::HALF_PLATE);
		break;
	case 8:
		armor = new Armor(ArmorType::FULL_PLATE);
		break;
	}

	//Build stats
	std::cout << "Rolling armor bonuses..." << std::endl << std::endl;
	int rerolls = 5;
	bool rolling = true;
	while (rolling) {
		armor->randomBonuses();
		std::cout << "Armor class bonus:\t" << armor->getArmorClassBonus() << std::endl << std::endl;
		if (rerolls > 0) {
			std::cout << "Are you happy with this bonus roll?" << std::endl;
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions)) {
			case 1:
				rolling = false;
				break;
			case 2:
				--rerolls;
				break;
			}
		}
		else {
			rolling = false;
		}
	}

	//Build name
	std::string itemName;
	bool choosingRandomName = true;
	std::cout << "What is the armor called?" << std::endl;
	switch (menu(builderNameOptions)) {
	case 1:
		while (choosingRandomName) {
			itemName = armorNames[Dice::roll("d100") - 1];
			std::cout << "The armor is called " << itemName << std::endl << std::endl;
			std::cout << "Are you happy with this item name?" << std::endl;
			if (menu(yesNoOptions) == 1) {
				choosingRandomName = false;
				armor->setName(itemName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		armor->setName(getUserInputString());
		std::cout << "The armor is named " << armor->getName() << "." << std::endl << std::endl;
		break;
	}

	_item = armor;
}

void ItemBuilder::buildBelt() {
	Belt* belt = new Belt();
	//Build stats
	std::cout << "Rolling belt bonuses..." << std::endl << std::endl;
	int rerolls = 5;
	bool rolling = true;
	while (rolling) {
		belt->randomBonuses();
		std::cout << "Strength bonus:\t\t" << belt->getStrengthBonus() << std::endl
			<< "Constitution bonus:\t" << belt->getConstitutionBonus() << std::endl << std::endl;
		if (rerolls > 0) {
			std::cout << "Are you happy with this bonus roll?" << std::endl;
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions)) {
			case 1:
				rolling = false;
				break;
			case 2:
				--rerolls;
				break;
			}
		}
		else {
			rolling = false;
		}
	}

	//Build name
	std::string itemName;
	bool choosingRandomName = true;
	std::cout << "What is the belt called?" << std::endl;
	switch (menu(builderNameOptions)) {
	case 1:
		while (choosingRandomName) {
			itemName = beltNames[Dice::roll("d100") - 1];
			std::cout << "The belt is called " << itemName << std::endl << std::endl;
			std::cout << "Are you happy with this item name?" << std::endl;
			if (menu(yesNoOptions) == 1) {
				choosingRandomName = false;
				belt->setName(itemName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		belt->setName(getUserInputString());
		std::cout << "The belt is named " << belt->getName() << "." << std::endl << std::endl;
		break;
	}

	_item = belt;
}

void ItemBuilder::buildBoots() {
	Boots* boots = new Boots();
	//Build stats
	std::cout << "Rolling boot bonuses..." << std::endl << std::endl;
	int rerolls = 5;
	bool rolling = true;
	while (rolling) {
		boots->randomBonuses();
		std::cout << "Armor class bonus:\t" << boots->getArmorClass() << std::endl
			<< "Dexterity bonus:\t" << boots->getDexterityBonus() << std::endl << std::endl;
		if (rerolls > 0) {
			std::cout << "Are you happy with this bonus roll?" << std::endl;
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions)) {
			case 1:
				rolling = false;
				break;
			case 2:
				--rerolls;
				break;
			}
		}
		else {
			rolling = false;
		}
	}

	//Build name
	std::string itemName;
	bool choosingRandomName = true;
	std::cout << "What are the boots called?" << std::endl;
	switch (menu(builderNameOptions)) {
	case 1:
		while (choosingRandomName) {
			itemName = bootNames[Dice::roll("d100") - 1];
			std::cout << "The boots are called " << itemName << std::endl << std::endl;
			std::cout << "Are you happy with this item name?" << std::endl;
			if (menu(yesNoOptions) == 1) {
				choosingRandomName = false;
				boots->setName(itemName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		boots->setName(getUserInputString());
		std::cout << "The boots are named " << boots->getName() << "." << std::endl << std::endl;
		break;
	}

	_item = boots;
}

void ItemBuilder::buildBracers() {
	Bracers* bracers = new Bracers();
	//Build stats
	std::cout << "Rolling bracer bonuses..." << std::endl << std::endl;
	int rerolls = 5;
	bool rolling = true;
	while (rolling) {
		bracers->randomBonuses();
		std::cout << "Armor class bonus:\t" << bracers->getArmorClass() << std::endl
			<< "Strength bonus:\t" << bracers->getStrengthBonus() << std::endl << std::endl;
		if (rerolls > 0) {
			std::cout << "Are you happy with this bonus roll?" << std::endl;
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions)) {
			case 1:
				rolling = false;
				break;
			case 2:
				--rerolls;
				break;
			}
		}
		else {
			rolling = false;
		}
	}

	//Build name
	std::string itemName;
	bool choosingRandomName = true;
	std::cout << "What are the bracers called?" << std::endl;
	switch (menu(builderNameOptions)) {
	case 1:
		while (choosingRandomName) {
			itemName = bracerNames[Dice::roll("d100") - 1];
			std::cout << "The bracers are called " << itemName << std::endl << std::endl;
			std::cout << "Are you happy with this item name?" << std::endl;
			if (menu(yesNoOptions) == 1) {
				choosingRandomName = false;
				bracers->setName(itemName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		bracers->setName(getUserInputString());
		std::cout << "The bracers are named " << bracers->getName() << "." << std::endl << std::endl;
		break;
	}

	_item = bracers;
}

void ItemBuilder::buildHelmet() {
	Helmet* helmet = new Helmet();
	//Build stats
	std::cout << "Rolling helmet bonuses..." << std::endl << std::endl;
	int rerolls = 5;
	bool rolling = true;
	while (rolling) {
		helmet->randomBonuses();
		std::cout << "Armor class bonus:\t" << helmet->getArmorClass() << std::endl
			<< "Intelligence bonus:\t" << helmet->getIntelligenceBonus() << std::endl 
			<< "Wisdom bonus:\t" << helmet->getWisdomBonus() << std::endl << std::endl;
		if (rerolls > 0) {
			std::cout << "Are you happy with this bonus roll?" << std::endl;
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions)) {
			case 1:
				rolling = false;
				break;
			case 2:
				--rerolls;
				break;
			}
		}
		else {
			rolling = false;
		}
	}

	//Build name
	std::string itemName;
	bool choosingRandomName = true;
	std::cout << "What is the helmet called?" << std::endl;
	switch (menu(builderNameOptions)) {
	case 1:
		while (choosingRandomName) {
			itemName = helmetNames[Dice::roll("d100") - 1];
			std::cout << "The helmet is called " << itemName << std::endl << std::endl;
			std::cout << "Are you happy with this item name?" << std::endl;
			if (menu(yesNoOptions) == 1) {
				choosingRandomName = false;
				helmet->setName(itemName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		helmet->setName(getUserInputString());
		std::cout << "The helmet is named " << helmet->getName() << "." << std::endl << std::endl;
		break;
	}

	_item = helmet;
}

void ItemBuilder::buildRing() {
	Ring* ring = new Ring();
	//Build stats
	std::cout << "Rolling ring bonuses..." << std::endl << std::endl;
	int rerolls = 5;
	bool rolling = true;
	while (rolling) {
		ring->randomBonuses();
		std::cout << "Armor class bonus:\t" << ring->getArmorClass() << std::endl
			<< "Strength bonus:\t" << ring->getStrengthBonus() << std::endl
			<< "Constitution bonus:\t" << ring->getConstitutionBonus() << std::endl
			<< "Wisdom bonus:\t" << ring->getWisdomBonus() << std::endl
			<< "Charisma bonus:\t" << ring->getCharismaBonus() << std::endl << std::endl;
		if (rerolls > 0) {
			std::cout << "Are you happy with this bonus roll?" << std::endl;
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions)) {
			case 1:
				rolling = false;
				break;
			case 2:
				--rerolls;
				break;
			}
		}
		else {
			rolling = false;
		}
	}

	//Build name
	std::string itemName;
	bool choosingRandomName = true;
	std::cout << "What is the ring called?" << std::endl;
	switch (menu(builderNameOptions)) {
	case 1:
		while (choosingRandomName) {
			itemName = ringNames[Dice::roll("d100") - 1];
			std::cout << "The ring is called " << itemName << std::endl << std::endl;
			std::cout << "Are you happy with this item name?" << std::endl;
			if (menu(yesNoOptions) == 1) {
				choosingRandomName = false;
				ring->setName(itemName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		ring->setName(getUserInputString());
		std::cout << "The ring is named " << ring->getName() << "." << std::endl << std::endl;
		break;
	}

	_item = ring;
}

void ItemBuilder::buildShield() {
	//Build armor type
	Shield* shield = &Shield();
	std::cout << "What type of shield do you want to create?" << std::endl;
	switch (menu(itemBuilderShieldTypeOptions)) {
	case 1:
		shield = new Shield(ShieldType::BUCKLER);
		break;
	case 2:
		shield = new Shield(ShieldType::HEAVY_SHIELD);
		break;
	case 3:
		shield = new Shield(ShieldType::TOWER_SHIELD);
		break;
	}

	//Build stats
	std::cout << "Rolling shield bonuses..." << std::endl << std::endl;
	int rerolls = 5;
	bool rolling = true;
	while (rolling) {
		shield->randomBonuses();
		std::cout << "Armor class bonus:\t" << shield->getArmorClassBonus() << std::endl << std::endl;
		if (rerolls > 0) {
			std::cout << "Are you happy with this bonus roll?" << std::endl;
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions)) {
			case 1:
				rolling = false;
				break;
			case 2:
				--rerolls;
				break;
			}
		}
		else {
			rolling = false;
		}
	}

	//Build name
	std::string itemName;
	bool choosingRandomName = true;
	std::cout << "What is the shield called?" << std::endl;
	switch (menu(builderNameOptions)) {
	case 1:
		while (choosingRandomName) {
			itemName = shieldNames[Dice::roll("d100") - 1];
			std::cout << "The shield is called " << itemName << std::endl << std::endl;
			std::cout << "Are you happy with this item name?" << std::endl;
			if (menu(yesNoOptions) == 1) {
				choosingRandomName = false;
				shield->setName(itemName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		shield->setName(getUserInputString());
		std::cout << "The shield is named " << shield->getName() << "." << std::endl << std::endl;
		break;
	}

	_item = shield;
}

void ItemBuilder::buildWeapon() {
	//Build armor type
	Weapon* weapon = &Weapon();
	std::cout << "What type of weapon do you want to create?" << std::endl;
	switch (menu(itemBuilderWeaponTypeOptions)) {
	case 1:
		weapon = new Weapon(WeaponType::LONGSWORD);
		break;
	case 2:
		weapon = new Weapon(WeaponType::LONGBOW);
		break;
	}

	//Build stats
	std::cout << "Rolling weapon bonuses..." << std::endl << std::endl;
	int rerolls = 5;
	bool rolling = true;
	while (rolling) {
		weapon->randomBonuses();
		std::cout << "Attack bonus:\t" << weapon->getAttackBonus() << std::endl
			<< "Damage bonus:\t" << weapon->getDamageBonus() << std::endl << std::endl;
		if (rerolls > 0) {
			std::cout << "Are you happy with this bonus roll?" << std::endl;
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions)) {
			case 1:
				rolling = false;
				break;
			case 2:
				--rerolls;
				break;
			}
		}
		else {
			rolling = false;
		}
	}

	//Build name
	std::string itemName;
	bool choosingRandomName = true;
	std::cout << "What is the weapon called?" << std::endl;
	switch (menu(builderNameOptions)) {
	case 1:
		while (choosingRandomName) {
			if (weapon->getWeaponType() == WeaponType::LONGSWORD) {
				itemName = longswordNames[Dice::roll("d100") - 1];
			}
			else if (weapon->getWeaponType() == WeaponType::LONGBOW) {
				itemName = longbowNames[Dice::roll("d100") - 1];
			}
			std::cout << "The weapon is called " << itemName << std::endl << std::endl;
			std::cout << "Are you happy with this item name?" << std::endl;
			if (menu(yesNoOptions) == 1) {
				choosingRandomName = false;
				weapon->setName(itemName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		weapon->setName(getUserInputString());
		std::cout << "The weapon is named " << weapon->getName() << "." << std::endl << std::endl;
		break;
	}

	_item = weapon;
}

