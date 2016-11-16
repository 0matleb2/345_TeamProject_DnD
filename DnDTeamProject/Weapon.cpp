#include "Weapon.h"
#include "Dice.h"
#include "Names.h"



Weapon::Weapon() : _attackBonus(0), _damageBonus(0) {

}

Weapon::Weapon(WeaponType weaponType) : Weapon() {
	switch (weaponType) {
	case WeaponType::LONGSWORD:
		setName(longswordNames[Dice::roll("1d100-1")]);
		setDamage("1d8");
		break;
	case WeaponType::LONGBOW:
		setName(longbowNames[Dice::roll("1d100-1")]);
		setDamage("1d8");
		break;
	}
	setWeaponType(weaponType);
	randomBonuses();
}


Weapon::~Weapon() {
}



//Accessors
WeaponType Weapon::getWeaponType() {
	return _weaponType;
}

int Weapon::getAttackBonus() {
	return _attackBonus;
}

int Weapon::getDamageBonus() {
	return _damageBonus;
}

std::string Weapon::getDamage() {
	return _damage;
}



//Mutators
void Weapon::setWeaponType(WeaponType weaponType) {
	_weaponType = weaponType;
}

void Weapon::setAttackBonus(int attackBonus) {
	_attackBonus = attackBonus;
}

void Weapon::setDamageBonus(int damageBonus) {
	_damageBonus = damageBonus;
}

void Weapon::setDamage(std::string damage) {
	_damage = damage;
}



void Weapon::randomBonuses() {
	int totalBonus = Dice::roll("1d5");
	int statBonuses[2] = { 0, 0 };
	for (int i = 0; i < totalBonus; ++i) {
		statBonuses[Dice::roll("1d2-1")]++;
	}
	setAttackBonus(statBonuses[0]);
	setDamageBonus(statBonuses[1]);
}


std::string Weapon::toString() {
	std::string s;
	s = Item::toString();
	if (getWeaponType() != WeaponType::DEFAULT)
		s += ", Weapon type: " + weaponTypeInfo[getWeaponType()];
	if (getDamage() != "")
		s += ", Damage: " + getDamage();
	if (getAttackBonus() != 0)
		s += ", Attack bonus: " + std::to_string(getAttackBonus());
	if (getDamageBonus() != 0)
		s += ", Damage bonus: " + std::to_string(getDamageBonus());
	return s;
}