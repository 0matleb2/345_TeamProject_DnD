#include <vector>
#include <string>
#include <conio.h>
#include <math.h>
#include "Character.h"
#include "Dice.h"
#include "Types.h"
#include "Map.h"
#include "CursorObserver.h"
#include "Menu.h"


Character::Character() : _lvl(1) {

	_inventory = new ItemContainer(20);

	_strategy = new DefaultStrategy();

}

Character::~Character() {
}



//Accessors
int Character::getX() {
	return _x;
}

int Character::getY() {
	return _y;
}

std::string Character::getName() {
	return _name;
}

int Character::getLvl() {
	return _lvl;
}

int Character::getHp() {
	return _hp;
}

int Character::getMaxHp() {
	return _maxHp;
}

int Character::getStrength() {
	return _strength;
}

int Character::getDexterity() {
	return _dexterity;
}

int Character::getConsitiution() {
	return _constitution;
}

int Character::getIntelligence() {
	return _intelligence;
}

int Character::getWisdom() {
	return _wisdom;
}

int Character::getCharisma() {
	return _charisma;
}

Armor* Character::getArmor(){
	return _armor;
}

Belt* Character::getBelt(){
	return _belt;
}

Boots* Character::getBoots(){
	return _boots;
}

Bracers* Character::getBracers(){
	return _bracers;
}

Helmet* Character::getHelmet(){
	return _helmet;
}

Ring* Character::getRing(){
	return _ring;
}

Shield* Character::getShield(){
	return _shield;
}

Weapon* Character::getWeapon(){
	return _weapon;
}

ItemContainer* Character::getInventory() {
	return _inventory;
}



//Mutators
void Character::setX(int x) {
	_x = x;
	_lastLog = getName() + " moves to " + std::to_string(_x) + ", " + std::to_string(_y);
	notify();
	_lastLog = "none";
}

void Character::setY(int y) {
	_lastLog = getName() + " moves to " + std::to_string(_x) + ", " + std::to_string(_y);
	_y = y;
	_lastLog = "none";
	notify();
}

void Character::setName(std::string name) {
	_name = name;
}

void Character::setLvl(int lvl) {
	_lvl = lvl;
}

void Character::setHp(int hp) {
	_hp = hp;
}

void Character::setMaxHp(int maxHp) {
	_maxHp = maxHp;
}

void Character::setStrength(int strength) {
	_strength = strength;
}

void Character::setDexterity(int dexterity) {
	_dexterity = dexterity;
}

void Character::setConsitiution(int constitution) {
	_constitution = constitution;
}

void Character::setIntelligence(int intelligence) {
	_intelligence = intelligence;
}

void Character::setWisdom(int wisdom) {
	_wisdom = wisdom;
}

void Character::setCharisma(int charisma) {
	_charisma = charisma;
}

void Character::setArmor(Armor * armor) {
	_armor = armor;
}

void Character::setBelt(Belt * belt) {
	_belt = belt;
}

void Character::setBoots(Boots * boots) {
	_boots = boots;
}

void Character::setBracers(Bracers * bracers) {
	_bracers = bracers;
}

void Character::setHelmet(Helmet * helmet) {
	_helmet = helmet;
}

void Character::setRing(Ring * ring) {
	_ring = ring;
}

void Character::setShield(Shield * shield) {
	_shield = shield;
}

void Character::setWeapon(Weapon * weapon) {
	_weapon = weapon;
}

void Character::setInventory(ItemContainer * inventory) {
	_inventory = inventory;
}

int Character::getTotalArmorClass() {
	int ac = 0;
	if (getArmor()) {
		ac += getArmor()->getArmorClass();
		ac += getArmor()->getArmorClassBonus();
	}
	if (getBoots()) {
		ac += getBoots()->getArmorClass();
	}
	if (getBracers()) {
		ac += getBracers()->getArmorClass();
	}
	if (getHelmet()) {
		ac += getHelmet()->getArmorClass();
	}
	if (getRing()) {
		ac += getRing()->getArmorClass();
	}
	if (getShield()) {
		ac += getShield()->getArmorClass();
		ac += getShield()->getArmorClassBonus();
	}
	return ac;
}


std::string Character::toString() {
	std::string s;
	s += std::string("[CHARACTER]\n")
		+ "Name: " + getName()
		+ "\nLvl: " + std::to_string(getLvl())
		+ ", Hp: " + std::to_string(getHp()) + "/" + std::to_string(getMaxHp())
		+ "\n\n[STATS]"
		+ "\nStrength: " + std::to_string(getStrength())
		+ ", Dexterity: " + std::to_string(getDexterity())
		+ ", Constitution: " + std::to_string(getConsitiution())
		+ ", Intelligence: " + std::to_string(getIntelligence())
		+ ", Wisdom: " + std::to_string(getWisdom())
		+ ", Charisma: " + std::to_string(getCharisma())
		+ "\n\n[EQUIPPED ITEMS]";
	if (getArmor()) {
		s += "\nArmor:\t\t" + getArmor()->toString();
	}
	if (getBelt()) {
		s += "\nBelt:\t\t" + getBelt()->toString();
	}
	if (getBoots()) {
		s += "\nBoots:\t\t" + getBoots()->toString();
	}
	if (getBracers()) {
		s += "\nBracers:\t" + getBracers()->toString();
	}
	if (getHelmet()) {
		s += "\nHelmet:\t\t" + getHelmet()->toString();
	}
	if (getRing()) {
		s += "\nRing:\t\t" + getRing()->toString();
	}
	if (getShield()) {
		s += "\nShield:\t\t" + getShield()->toString();
	}
	if (getWeapon()) {
		s += "\nWeapon:\t\t" + getWeapon()->toString();
	}
	s += "\n\n[INVENTORY]\n"
		+ getInventory()->toString() + "\n";
	return s;
}


int Character::abilityScoreToModifier(int score) {
	return (score / 2) - 5;
}

void Character::move(Map* context) {
	
	unsigned char keypress = _getch();
	if (keypress == 0 || keypress == 0xE0) { // Arrow key presses require this first char to be ignored
		keypress = _getch();
	}

	switch (keypress) {
	case 'W':
	case 'w':
	case 72: //Arrow key UP
		if (context->isCellEmpty(_x, _y - 1)) {
			setY(_y - 1);
		}
		break;
	case 'A':
	case 'a':
	case 75: //Arrow key LEFT
		if (context->isCellEmpty(_x - 1, _y)) {
			setX(_x - 1);
		}
		break;
	case 'S':
	case 's':
	case 80: //Arrow key DOWN
		if (context->isCellEmpty(_x, _y + 1)) {
			setY(_y + 1);
		}
		break;
	case 'D':
	case 'd':
	case 77: //Arrow key RIGHT
		if (context->isCellEmpty(_x + 1, _y)) {
			setX(_x + 1);
		}
		break;
	case 'c':
	case 'C': //In game menu
		characterMenu();
		context->draw();
		break;
	}
}

void Character::characterMenu() {
	bool onCharacterMenu = true;
	while (onCharacterMenu) {
		system("cls");
		std::cout << toString() << std::endl;
		switch (menu(inGameMenuOptions, "What do you want to do?")) {
		case 1: //Equip an item
			equipItemMenu();
			break;
		case 2: //Unequip an item
			unequipItemMenu();
			break;
		case 3: //Discard an item
			discardItemMenu();
			break;
		case 4: //Return to game
			onCharacterMenu = false;
			break;
		}

	}
}

void Character::equipItemMenu() {
	std::vector<std::string> inventoryItemsMenuOptions;
	std::vector<Item*> inventory = getInventory()->getContents();
	for (int i = 0, n = inventory.size(); i < n; ++i) {
		inventoryItemsMenuOptions.push_back(inventory[i]->toString());
	}
	inventoryItemsMenuOptions.push_back("Cancel");
	int choice = menu(inventoryItemsMenuOptions, "Which item do you want to equip?") - 1;
	if (choice == inventoryItemsMenuOptions.size() - 1)
		return;
	equip(getInventory()->withdrawItem(choice));
	return;
}

void Character::unequipItemMenu() {
	std::vector<std::string> equippedItemsMenuOptions;
	equippedItemsMenuOptions.push_back("Armor:\t\t" + (getArmor() ? getArmor()->toString() : ""));
	equippedItemsMenuOptions.push_back("Belt:\t\t" + (getBelt() ? getBelt()->toString() : ""));
	equippedItemsMenuOptions.push_back("Boots:\t\t" + (getBoots() ? getBoots()->toString() : ""));
	equippedItemsMenuOptions.push_back("Bracers:\t\t" + (getBracers() ? getBracers()->toString() : ""));
	equippedItemsMenuOptions.push_back("Helmet:\t\t" + (getHelmet() ? getHelmet()->toString() : ""));
	equippedItemsMenuOptions.push_back("Ring:\t\t" + (getRing() ? getRing()->toString() : ""));
	equippedItemsMenuOptions.push_back("Shield:\t\t" + (getShield() ? getShield()->toString() : ""));
	equippedItemsMenuOptions.push_back("Weapon:\t\t" + (getWeapon() ? getWeapon()->toString() : ""));
	equippedItemsMenuOptions.push_back("Cancel");
	int choice = menu(equippedItemsMenuOptions, "Which item do you want to unequip?");
	if (choice == equippedItemsMenuOptions.size())
		return;
	switch (choice) {
	case 1: //Armor
		if (_armor) {
			_inventory->depositItem(*_armor);
			_armor = nullptr;
		}
		break;
	case 2: //Belt
		if (_belt) {
			_inventory->depositItem(*_belt);
			_belt = nullptr;
		}
		break;
	case 3: //Boots
		if (_boots) {
			_inventory->depositItem(*_boots);
			_boots = nullptr;
		}
		break;
	case 4: //Bracers
		if (_bracers) {
			_inventory->depositItem(*_bracers);
			_bracers = nullptr;
		}
		break;
	case 5: //Helmet
		if (_helmet) {
			_inventory->depositItem(*_helmet);
			_helmet = nullptr;
		}
		break;
	case 6: //Ring
		if (_ring) {
			_inventory->depositItem(*_ring);
			_ring = nullptr;
		}
		break;
	case 7: //Shield
		if (_shield) {
			_inventory->depositItem(*_shield);
			_shield = nullptr;
		}
		break;
	case 8: //Weapon
		if (_weapon) {
			_inventory->depositItem(*_weapon);
			_weapon = nullptr;
		}
		break;
	}
}


void Character::discardItemMenu() {
	std::vector<std::string> inventoryItemsMenuOptions;
	std::vector<Item*> inventory = getInventory()->getContents();
	for (int i = 0, n = inventory.size(); i < n; ++i) {
		inventoryItemsMenuOptions.push_back(inventory[i]->toString());
	}
	inventoryItemsMenuOptions.push_back("Cancel");
	int choice = menu(inventoryItemsMenuOptions, "Which item do you want to discard?") - 1;
	if (choice == inventoryItemsMenuOptions.size() - 1)
		return;
	if (menu(yesNoOptions, "Are you sure you want to discard " + inventory[choice]->getName() + "?") == 1)
		_inventory->withdrawItem(choice);
	return;
}

void Character::equip(Item* item) {
	switch (item->getItemType()) {
	case ItemType::ARMOR:
		if (_armor)
			_inventory->depositItem(*_armor);
		_armor = dynamic_cast<Armor*>(item);
		break;
	case ItemType::BELT:
		if (_belt)
			_inventory->depositItem(*_belt);
		_belt = dynamic_cast<Belt*>(item);
		break;
	case ItemType::BOOTS:
		if (_boots)
			_inventory->depositItem(*_boots);
		_boots = dynamic_cast<Boots*>(item);
		break;
	case ItemType::BRACERS:
		if (_bracers)
			_inventory->depositItem(*_bracers);
		_bracers = dynamic_cast<Bracers*>(item);
		break;
	case ItemType::HELMET:
		if (_helmet)
			_inventory->depositItem(*_helmet);
		_helmet = dynamic_cast<Helmet*>(item);
		break;
	case ItemType::RING:
		if (_ring)
			_inventory->depositItem(*_ring);
		_ring = dynamic_cast<Ring*>(item);
		break;
	case ItemType::SHIELD:
		if (_shield)
			_inventory->depositItem(*_shield);
		_shield = dynamic_cast<Shield*>(item);
		break;
	case ItemType::WEAPON:
		if (_weapon)
			_inventory->depositItem(*_weapon);
		_weapon = dynamic_cast<Weapon*>(item);
		break;
	}
}

Character* Character::selectAttackTarget(Map* context) {

	context->setDrawSuffix("<Attack Phase>\n\nSelecting attack target...\n\nUse [W, A, S, D] to move the cursor.\nPress [+] to inspect an NPC.\nPress [Enter] to select a target to attack.\nPress [Esc] to continue without attacking.");

	Cursor* attackSelectCursor = new Cursor();
	CursorObserver* cursorObserver = new CursorObserver(attackSelectCursor, context);
	context->setCursor(attackSelectCursor);
	attackSelectCursor->setX(_x);
	attackSelectCursor->setY(_y);

	std::vector<Character*> levelNPCs = context->getNpcCharacters();

	while (true) {
		int cursorX = context->getCursor()->getX();
		int cursorY = context->getCursor()->getY();
		unsigned char keypress = _getch();
		if (keypress == 0 || keypress == 0xE0) { // Arrow key presses require this first char to be ignored
			keypress = _getch();
		}
		switch (keypress) {
		case 'W':
		case 'w':
		case 72: //Arrow key UP
			if (cursorY > 0 && (cursorY > _y - _weapon->getRange()))
				context->getCursor()->setY(cursorY - 1);
			break;
		case 'A':
		case 'a':
		case 75: //Arrow key LEFT
			if (cursorX > 0 && (cursorX > _x - _weapon->getRange()))
				context->getCursor()->setX(cursorX - 1);
			break;
		case 'S':
		case 's':
		case 80: //Arrow key DOWN
			if (cursorY < (context->getHeight() - 1) && (cursorY < _y + _weapon->getRange()))
				context->getCursor()->setY(cursorY + 1);
			break;
		case 'D':
		case 'd':
		case 77: //Arrow key RIGHT
			if (cursorX < (context->getWidth() - 1) && (cursorX < _x + _weapon->getRange()))
				context->getCursor()->setX(cursorX + 1);
			break;
		case '+': //Inspect
			for (int i = 0, n = levelNPCs.size(); i < n; ++i) {
				if (cursorX == levelNPCs[i]->getX() && cursorY == levelNPCs[i]->getY()) {
					context->draw();
					std::cout << levelNPCs[i]->toString() << std::endl;
				}
			}
			break;
		case '\r': //ENTER (attack target)
			for (int i = 0, n = levelNPCs.size(); i < n; ++i) {
				if (cursorX == levelNPCs[i]->getX() && cursorY == levelNPCs[i]->getY()) {
					context->setCursor(nullptr);
					delete attackSelectCursor;
					delete cursorObserver;
					return levelNPCs[i];
				}
			}
			break;
		case 27: //ESC (cancel attack)
			context->setCursor(nullptr);
			delete attackSelectCursor;
			delete cursorObserver;
			context->draw();
			return nullptr;
			break;
		case 'c':
		case 'C': //In game menu
			characterMenu();
			context->draw();
			break;
		}
	}
}

bool Character::npcInRange(Map* context) {
	int range = _weapon->getRange();
	for (int h = -range; h < range + 1; ++h) {
		for (int w = -range; w < range + 1; ++w) {
			if (h + _y >= 0 && h + _y <= context->getHeight() - 1 && w + _x >= 0 && w + _x <= context->getWidth() - 1) {
				for (int i = 0, n = context->getNpcCharacters().size(); i < n; ++i) {
					if (w + _x == context->getNpcCharacters()[i]->getX() && h + _y == context->getNpcCharacters()[i]->getY()) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Character::chestInRange(Map* context) {
	for (int h = -1; h < 2; ++h) {
		for (int w = -1; w < 2; ++w) {
			if (h + _y >= 0 && h + _y <= context->getHeight() - 1 && w + _x >= 0 && w + _x <= context->getWidth() - 1) {
				for (int i = 0, n = context->getChests().size(); i < n; ++i) {
					if (w + _x == context->getChests()[i]->getX() && h + _y == context->getChests()[i]->getY()) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

Chest* Character::selectLootTarget(Map* context) {

	context->setDrawSuffix("<Loot Phase>\n\nSelecting loot target...\n\nUse [W, A, S, D] to move the cursor.\nPress [+] to inspect a Chest.\nPress [Enter] to loot the chest.\nPress [Esc] to continue without looting.");

	Cursor* lootSelectCursor = new Cursor();
	CursorObserver* cursorObserver = new CursorObserver(lootSelectCursor, context);
	context->setCursor(lootSelectCursor);
	lootSelectCursor->setX(_x);
	lootSelectCursor->setY(_y);

	std::vector<Chest*> levelChests = context->getChests();

	while (true) {
		int cursorX = context->getCursor()->getX();
		int cursorY = context->getCursor()->getY();
		unsigned char keypress = _getch();
		if (keypress == 0 || keypress == 0xE0) { // Arrow key presses require this first char to be ignored
			keypress = _getch();
		}
		switch (keypress) {
		case 'W':
		case 'w':
		case 72: //Arrow key UP
			if (cursorY > 0 && (cursorY > _y - 1))
				context->getCursor()->setY(cursorY - 1);
			break;
		case 'A':
		case 'a':
		case 75: //Arrow key LEFT
			if (cursorX > 0 && (cursorX > _x - 1))
				context->getCursor()->setX(cursorX - 1);
			break;
		case 'S':
		case 's':
		case 80: //Arrow key DOWN
			if (cursorY < (context->getHeight() - 1) && (cursorY < _y + 1))
				context->getCursor()->setY(cursorY + 1);
			break;
		case 'D':
		case 'd':
		case 77: //Arrow key RIGHT
			if (cursorX < (context->getWidth() - 1) && (cursorX < _x + 1))
				context->getCursor()->setX(cursorX + 1);
			break;
		case '+': //Inspect
			for (int i = 0, n = levelChests.size(); i < n; ++i) {
				if (cursorX == levelChests[i]->getX() && cursorY == levelChests[i]->getY()) {
					context->draw();
					std::cout << levelChests[i]->toString() << std::endl;
				}
			}
			break;
		case '\r': //ENTER (loot target)
			for (int i = 0, n = levelChests.size(); i < n; ++i) {
				if (cursorX == levelChests[i]->getX() && cursorY == levelChests[i]->getY()) {
					context->setCursor(nullptr);
					delete lootSelectCursor;
					delete cursorObserver;
					return levelChests[i];
				}
			}
			break;
		case 27: //ESC (cancel attack)
			context->setCursor(nullptr);
			delete lootSelectCursor;
			delete cursorObserver;
			context->draw();
			return nullptr;
			break;
		case 'c':
		case 'C': //In game menu
			characterMenu();
			context->draw();
			break;
		}
	}
}

void Character::loot(Chest* target, Map* context) {
	std::string postLootSuffix;
	for (int i = 0, n = target->getContents().size(); i < n; ++i) {
		Item* withdrawnItem = target->withdrawItem(i);
		postLootSuffix += "Looted:  " + withdrawnItem->toString() + "\n";
		getInventory()->depositItem(*withdrawnItem);
	}
	context->resolveEmptyChests();
	postLootSuffix += "\nPress any key to continue...";
	context->setDrawSuffix(postLootSuffix);
	context->draw();
	_getch();
}

void Character::attack(Character* target, Map* context) {
	
	//change target to hostile, wont affect player as player strategy isnt called
	target->setStrategy(2);
	
	//Loop for multiple attacks;
	int numAttacks = (getLvl() - 1) / 5 + 1;
	std::string postAttackSuffix;
	postAttackSuffix += "Attacking " + target->getName() + "...\n\n" + target->getName() + " has a total armor class of " + std::to_string(target->getTotalArmorClass()) + ".";
	for (int i = 0; i < numAttacks; ++i) {
		//Attack roll
		int attackBonus = getLvl() - 5 * i;
		if (_weapon) {
			attackBonus += _weapon->getAttackBonus();
			if (_weapon->getWeaponType() == WeaponType::LONGSWORD)
				attackBonus += abilityScoreToModifier(_strength);
			else if (_weapon->getWeaponType() == WeaponType::LONGBOW)
				attackBonus += abilityScoreToModifier(_dexterity);
		}
		int attackRoll = Dice::roll("d20");
		postAttackSuffix +=  "\n\n[Attack #" + std::to_string(i + 1) + "]\nAttack roll : " + std::to_string(attackRoll) + ", Attack bonus : " + std::to_string(attackBonus);
		if (attackRoll + attackBonus >= getTotalArmorClass()) {
			//Damage roll
			int damageRoll = Dice::roll(_weapon->getDamage()) + _weapon->getDamageBonus();

			_lastLog = getName() + "'s attack hit " + target->getName() + " for " + std::to_string(damageRoll) + " damage.";
			notify();
			postAttackSuffix += "\nAttack hit!\n" + std::to_string(damageRoll) + " damage done to " + target->getName();
			_lastLog = "none";
			target->setHp(target->getHp() - damageRoll);
		}
		else {
			// logger makes use of an observer and the _lastLog string to log
			_lastLog = getName() + "'s attack missed!";
			notify();
			postAttackSuffix += "\nAttack missed!";
			_lastLog = "none";
		}	
	}
	if (target->getHp() <= 0) {
		postAttackSuffix += "\n\n" + target->getName() + " has been killed!";
	}
	context->resolveNpcDeaths();
	postAttackSuffix += "\n\nPress any key to continue...";
	context->setDrawSuffix(postAttackSuffix);
	context->draw();
	_getch();
}


void Character::scale(int targetLevel) {
	double averageHpUpPerLvl = (double)(_maxHp - 10) / (double)(_lvl - 1);
	_maxHp = 10 + (int)std::round((targetLevel - 1) * averageHpUpPerLvl);
	_hp = _maxHp;
	_lvl = targetLevel;
	double scaledLevelMultiplier = (_lvl > 10) ? 5.0 : (_lvl / 2.0);
	if (_armor)
		_armor->setArmorClassBonus((int)round((_armor->getArmorClassBonus() / 5.0) * scaledLevelMultiplier ));
	if (_belt) {
		_belt->setConstitutionBonus((int)round((_belt->getConstitutionBonus() / 5.0) * scaledLevelMultiplier));
		_belt->setStrengthBonus((int)round((_belt->getStrengthBonus() / 5.0) * scaledLevelMultiplier));
	}
	if (_boots) {
		_boots->setArmorClass((int)round((_boots->getArmorClass() / 5.0) * scaledLevelMultiplier));
		_boots->setDexterityBonus((int)round((_boots->getDexterityBonus() / 5.0) * scaledLevelMultiplier));
	}
	if (_bracers) {
		_bracers->setArmorClass((int)round((_bracers->getArmorClass() / 5.0) * scaledLevelMultiplier));
		_bracers->setStrengthBonus((int)round((_bracers->getStrengthBonus() / 5.0) * scaledLevelMultiplier));
	}
	if (_helmet) {
		_helmet->setArmorClass((int)round((_helmet->getArmorClass() / 5.0) * scaledLevelMultiplier));
		_helmet->setIntelligenceBonus((int)round((_helmet->getIntelligenceBonus() / 5.0) * scaledLevelMultiplier));
		_helmet->setWisdomBonus((int)round((_helmet->getWisdomBonus() / 5.0) * scaledLevelMultiplier));
	}
	if (_ring) {
		_ring->setArmorClass((int)round((_ring->getArmorClass() / 5.0) * scaledLevelMultiplier));
		_ring->setConstitutionBonus((int)round((_ring->getConstitutionBonus() / 5.0) * scaledLevelMultiplier));
		_ring->setWisdomBonus((int)round((_ring->getWisdomBonus() / 5.0) * scaledLevelMultiplier));
		_ring->setStrengthBonus((int)round((_ring->getStrengthBonus() / 5.0) * scaledLevelMultiplier));
		_ring->setCharismaBonus((int)round((_ring->getCharismaBonus() / 5.0) * scaledLevelMultiplier));
	}
	if (_shield) {
		_shield->setArmorClassBonus((int)round((_shield->getArmorClassBonus() / 5.0) * scaledLevelMultiplier));
	}
	if (_weapon) {
		_weapon->setAttackBonus((int)round((_weapon->getAttackBonus() / 5.0) * scaledLevelMultiplier));
		_weapon->setDamageBonus((int)round((_weapon->getDamageBonus() / 5.0) * scaledLevelMultiplier));
	}
}

void Character::levelUp() {
	++_lvl;
	_maxHp += Dice::roll("1d10") + abilityScoreToModifier(_constitution);
	_hp = _maxHp;
}



std::string Character::getLog()
{
	return _lastLog;
}




bool Character::operator==(const Character & character) const {
	return _name == character._name &&
		_lvl == character._lvl &&
		_hp == character._hp &&
		_maxHp == character._maxHp &&
		_strength == character._strength &&
		_dexterity == character._dexterity &&
		_constitution == character._constitution &&
		_intelligence == character._intelligence &&
		_wisdom == character._wisdom &&
		_charisma == character._charisma;
		
	/*  &&
		_armor == character._armor &&
		_belt == character._belt &&
		_boots == character._boots &&
		_bracers == character._bracers &&
		_helmet == character._helmet &&
		_ring == character._ring &&
		_shield == character._shield &&
		_weapon == character._weapon &&
		_inventory == character._inventory;
		*/
}

//strategy-related

void Character::setStrategy(int choice)
{
	switch (choice)
	{
	case 0:
		_strategy = new DefaultStrategy();
		break;
	case 1:
		_strategy = new FriendlyStrategy();
		break;
	case 2:
		_strategy = new HostileStrategy();
	default:
		break;
	}

	
}

void Character::executeStrat(Map* context)
{
		_strategy->execute(this, context);
}