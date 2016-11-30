#include <vector>
#include <string>
#include <conio.h>
#include "Character.h"
#include "Dice.h"
#include "Types.h"
#include "Map.h"
#include "CursorObserver.h"


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
	notify();
}

void Character::setY(int y) {
	_y = y;
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

	bool selectingAttackTarget = true;
	while (selectingAttackTarget) {
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
		}
	}
}

void Character::attack(Character* target, Map* context) {
	//Loop for multiple attacks;
	int numAttacks = (getLvl() - 1) / 5 + 1;
	std::string postAttackSuffix;
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
		postAttackSuffix += "Attacking " + target->getName() + "...\n\n" + "[Attack #" + std::to_string(i + 1) + "]\nAttack roll: " + std::to_string(attackRoll) + ", Attack bonus:" + std::to_string(attackBonus);
		if (attackRoll + attackBonus >= getTotalArmorClass()) {
			//Damage roll
			int damageRoll = Dice::roll(_weapon->getDamage()) + _weapon->getDamageBonus();
			postAttackSuffix += "\nAttack hit!\n" + std::to_string(damageRoll) + " damage done to " + target->getName();
			target->setHp(target->getHp() - damageRoll);
		}
		else {
			postAttackSuffix += "\nAttack missed!";
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



void Character::levelUp() {
	++_lvl;
	_maxHp += Dice::roll("1d10") + abilityScoreToModifier(_constitution);
	_hp = _maxHp;
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
	default:
		break;
	}

	
}

void Character::executeStrat(Map* context)
{
	_strategy->execute(this, context);
}