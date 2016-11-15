#pragma once
#include "Item.h"
#include "Types.h"



class Weapon : public Item {

public:

	Weapon();
	Weapon(WeaponType weaponType);
	~Weapon();

	WeaponType getWeaponType();
	int getAttackBonus();
	int getDamageBonus();
	std::string getDamage();

	void setWeaponType(WeaponType weaponType);
	void setAttackBonus(int attackBonus);
	void setDamageBonus(int damageBonus);
	void setDamage(std::string damage);

	void randomBonuses();

	std::string toString();

private:

	WeaponType _weaponType;
	int _attackBonus;
	int _damageBonus;
	std::string _damage;

};

