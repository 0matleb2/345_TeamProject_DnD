#include <vector>
#include <string>
#include "Character.h"
#include "Dice.h"
#include "Types.h"


Character::Character() : _lvl(1) {

	_strength = Dice::roll("(3)4d6");
	_dexterity = Dice::roll("(3)4d6");
	_constitution = Dice::roll("(3)4d6");
	_intelligence = Dice::roll("(3)4d6");
	_wisdom = Dice::roll("(3)4d6");
	_charisma = Dice::roll("(3)4d6");

	_inventory = new ItemContainer(20);
	_maxHp = 10 + abilityScoreToModifier(_constitution);
	_hp = _maxHp;
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
}

void Character::setY(int y) {
	_y = y;
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



void Character::levelUp() {
	++_lvl;
	_maxHp += Dice::roll("1d10") + abilityScoreToModifier(_constitution);
	_hp = _maxHp;
}

void Character::attack()
{
	_lastLog = getName() + " attacks X.";

	notify();

	_lastLog = "none";
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
