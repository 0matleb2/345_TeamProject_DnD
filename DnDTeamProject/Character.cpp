//!Implementation of the Character class.

#pragma once

#include <iostream>
#include <math.h>		//for floor()
#include "Character.h"
#include "Dice.h"   
#include "Item.h"

//! Default constructor, will most likely not be used at all outside of testing purposes
Character::Character() {
	_name = "UNNAMED CHARACTER";
	_class = "Fighter";
	_lvl = 1;
	_xp= 0;
	_isAlive = true;
	updateBaseAttackBonus();

	_abilityScores[0] = 12;
	_abilityScores[1] = 12;
	_abilityScores[2] = 12;
	_abilityScores[3] = 12;
	_abilityScores[4] = 12;
	_abilityScores[5] = 12;

	_strengthModifier = abilityModifier(_abilityScores[0]);
	_dexterityModifier = abilityModifier(_abilityScores[1]);
	_constitutionModifier = abilityModifier(_abilityScores[2]);
	_intelligenceModifier = abilityModifier(_abilityScores[3]);
	_wisdomModifier = abilityModifier(_abilityScores[4]);
	_charismaModifier = abilityModifier(_abilityScores[5]);
	_armorClass += 10 + _dexterityModifier;

	//hit points
	setInitialMaxHP(_lvl, abilityModifier(_abilityScores[2]));		//_abilityScores[2] is constitution
	_hp = _maxHp;
	//equipment
	_weapon = new Weapon("Basic Sword", ItemType::WEAPON, std::vector<Enchant*>(), 0, WeaponType::MELEE);
	_equipment[0] = new Equipment("Basic Shield", ItemType::SHIELD, std::vector<Enchant*>());
	_equipment[1] = new Equipment("Basic Helmet", ItemType::HELMET, std::vector<Enchant*>());
	_equipment[2] = new Equipment("Basic Armor", ItemType::ARMOR, std::vector<Enchant*>());
	_equipment[3] = new Equipment("Basic Belt", ItemType::BELT, std::vector<Enchant*>());
	_equipment[4] = new Equipment("Basic Boots", ItemType::BOOTS, std::vector<Enchant*>());
	_equipment[5] = new Equipment("Basic Ring", ItemType::RING, std::vector<Enchant*>());
	_backpack = new ItemContainer();
	updateModifiersAndBonuses();
}

//! Object constructor as per assignment instructions
//! @param charaClass: The wanted character class (Fighter is the only choice at the moment)
//! @param lvl: The wanted character _lvl
//! All Stat with the exception of _attackBonus() are generated upon creation
Character::Character(std::string charaName,  std::string charaClass, int lvl) {
	_name = charaName;
	_class = charaClass;
	_lvl = lvl;
	_isAlive = true;
	// gives initial experience points based on _lvl entered
	_xp = 0;
	int lev_temp = _lvl;
	while (lev_temp > 1) {
		_xp += (lev_temp - 1) * 1000;
		lev_temp--;
	}
	updateBaseAttackBonus();

	//rolling for initial Stat
	std::vector<int> vec;
	// Rolls 4d20 and keeps the three highest rolls for each ability score
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			vec.push_back(Dice::roll("d6"));
		}
		std::sort(vec.begin(), vec.end());
		_abilityScores[i] = (vec[0] + vec[1] + vec[2]);
		vec.clear();
	}

	_strengthModifier = abilityModifier(_abilityScores[0]);
	_dexterityModifier = abilityModifier(_abilityScores[1]);
	_constitutionModifier = abilityModifier(_abilityScores[2]);
	_intelligenceModifier = abilityModifier(_abilityScores[3]);
	_wisdomModifier = abilityModifier(_abilityScores[4]);
	_charismaModifier = abilityModifier(_abilityScores[5]);
	_armorClass += 10 + _dexterityModifier;

	//setting hit points
	setInitialMaxHP(_lvl, _constitutionModifier);
	_hp = _maxHp;

	//equipment
	_weapon = new Weapon("Basic Sword", ItemType::WEAPON, std::vector<Enchant*>(), 0, WeaponType::MELEE);
	_equipment[0] = new Equipment("Basic Shield", ItemType::SHIELD, std::vector<Enchant*>());
	_equipment[1] = new Equipment("Basic Helmet", ItemType::HELMET, std::vector<Enchant*>());
	_equipment[2] = new Equipment("Basic Armor", ItemType::ARMOR, std::vector<Enchant*>());
	_equipment[3] = new Equipment("Basic Belt", ItemType::BELT, std::vector<Enchant*>());
	_equipment[4] = new Equipment("Basic Boots", ItemType::BOOTS, std::vector<Enchant*>());
	_equipment[5] = new Equipment("Basic Ring", ItemType::RING, std::vector<Enchant*>());
	_backpack = new ItemContainer();

	_damageBonus = _strengthModifier;
	updateAttackBonus();
}

Character::Character(std::string name, std::string charaClass, int lvl, int str, int dex, int con, int intel, int wis, int cha) {
	_name = name;
	_class = charaClass;
	_lvl = lvl;
	_isAlive = true;
	// gives initial experience points based on _lvl entered
	_xp = 0;
	int lev_temp = _lvl;
	while (lev_temp > 1) {
		_xp += (lev_temp - 1) * 1000;
		lev_temp--;
	}
	updateBaseAttackBonus();

	_abilityScores[0] = str;
	_abilityScores[1] = dex;
	_abilityScores[2] = con;
	_abilityScores[3] = intel;
	_abilityScores[4] = wis;
	_abilityScores[5] = cha;

	_strengthModifier = abilityModifier(_abilityScores[0]);
	_dexterityModifier = abilityModifier(_abilityScores[1]);
	_constitutionModifier = abilityModifier(_abilityScores[2]);
	_intelligenceModifier = abilityModifier(_abilityScores[3]);
	_wisdomModifier = abilityModifier(_abilityScores[4]);
	_charismaModifier = abilityModifier(_abilityScores[5]);
	_armorClass += 10 + _dexterityModifier;

	//setting hit points
	setInitialMaxHP(_lvl, _constitutionModifier);
	_hp = _maxHp;
	//equipment
	_weapon = new Weapon("Basic Sword", ItemType::WEAPON, std::vector<Enchant*>(), 0, WeaponType::MELEE);
	_equipment[0] = new Equipment("Basic Shield", ItemType::SHIELD, std::vector<Enchant*>());
	_equipment[1] = new Equipment("Basic Helmet", ItemType::HELMET, std::vector<Enchant*>());
	_equipment[2] = new Equipment("Basic Armor", ItemType::ARMOR, std::vector<Enchant*>());
	_equipment[3] = new Equipment("Basic Belt", ItemType::BELT, std::vector<Enchant*>());
	_equipment[4] = new Equipment("Basic Boots", ItemType::BOOTS, std::vector<Enchant*>());
	_equipment[5] = new Equipment("Basic Ring", ItemType::RING, std::vector<Enchant*>());
	_backpack = new ItemContainer();

	_damageBonus = _strengthModifier;
	updateAttackBonus();
}

//!Object constructor made specifically for the CPP Unit test provided
//!@param str: Character's strength attribute
//!@param dex: Character's dexterity attribute
//!@param con: Character's constitution attribute
//!@param intel: Character's intelligence attribute
//!@param wis: Character's wisdom attribute
//!@param cha: Character's charisma attribute
Character::Character(int str, int dex, int con, int intel, int wis, int cha) {
	_name = "UNNAMED CHARACTER";
	_class = "Fighter";
	_lvl = 1;
	_isAlive = true;
	updateBaseAttackBonus();

	_abilityScores[0] = str;
	_abilityScores[1] = dex;
	_abilityScores[2] = con;
	_abilityScores[3] = intel;
	_abilityScores[4] = wis;
	_abilityScores[5] = cha;

	_strengthModifier = abilityModifier(_abilityScores[0]);
	_dexterityModifier = abilityModifier(_abilityScores[1]);
	_constitutionModifier = abilityModifier(_abilityScores[2]);
	_intelligenceModifier = abilityModifier(_abilityScores[3]);
	_wisdomModifier = abilityModifier(_abilityScores[4]);
	_charismaModifier = abilityModifier(_abilityScores[5]);
	_armorClass += 10 + _dexterityModifier;

	//hit points
	_maxHp = 10;
	_hp = 10;
	//equipment
	_weapon = new Weapon("Basic Sword", ItemType::WEAPON, std::vector<Enchant*>(), 0, WeaponType::MELEE);
	_equipment[0] = new Equipment("Basic Shield", ItemType::SHIELD, std::vector<Enchant*>());
	_equipment[1] = new Equipment("Basic Helmet", ItemType::HELMET, std::vector<Enchant*>());
	_equipment[2] = new Equipment("Basic Armor", ItemType::ARMOR, std::vector<Enchant*>());
	_equipment[3] = new Equipment("Basic Belt", ItemType::BELT, std::vector<Enchant*>());
	_equipment[4] = new Equipment("Basic Boots", ItemType::BOOTS, std::vector<Enchant*>());
	_equipment[5] = new Equipment("Basic Ring", ItemType::RING, std::vector<Enchant*>());
	_backpack = new ItemContainer();

	_damageBonus = _strengthModifier;
	updateAttackBonus();
}

//! copy constructor
Character::Character(const Character& orig) :
	_name(orig._name),
	_class(orig._class),
	_lvl(orig._lvl),
	_xp(orig._xp),
	_maxHp(orig._maxHp),
	_hp(orig._hp),
	_isAlive(orig._isAlive),
	_armorClass(orig._armorClass),
	_damageBonus(orig._damageBonus),
	_strengthModifier(orig._strengthModifier),
	_dexterityModifier(orig._dexterityModifier),
	_intelligenceModifier(orig._intelligenceModifier),
	_wisdomModifier(orig._wisdomModifier),
	_charismaModifier(orig._charismaModifier),
	_constitutionModifier(orig._constitutionModifier)
{
	for (int i = 0; i < 6; i++) {
		_abilityScores[i] = orig._abilityScores[i];
	}
	_weapon = orig._weapon->clone();
	for (int i = 0; i < 6; i++) {
		_equipment[i] = orig._equipment[i]->clone();
	}
	for (int i = 0; i < orig._backpack->getSize(); i++) {
		_backpack->addItem(orig._backpack->getItem(i)->clone());
	}
	for (int i = 0; i < 4; i++) {
		_baseAttackBonus[i] = orig._baseAttackBonus[i];
	}
	for (int i = 0; i < 4; i++) {
		_attackBonus[i] = orig._attackBonus[i];
	}
}

//! Object destructor
Character::~Character() {
	
	delete _weapon;
	_weapon = NULL;

	for (int i = 0; i < 6; i++)	{
		delete _equipment[i];
		_equipment[i] = NULL;
	}

	delete _backpack;
	_backpack = NULL;

	std::cout << "Character object has been destroyed" << std::endl;
}

//! Function for giving max HP for a newly-created character.
//! Checks if a _lvl higher than 1 was given at creation and adds more to the max hit point pool based on that
//! using the @_lvlUpHitPointGain() function. Every subsequent _lvl generates a number between 1 and 10, plus _constitutionModifier
void Character::setInitialMaxHP(int lvl, int modifier) {
	//_hp set to -1 initially to show to _lvlUpHitPointGain() function that the character is still being created,
	//as opposed to being already existent, thus it is unnecessary to print out any messages displaying all the HP gains (see in _lvlUpHitPointGain())
	_hp = -1;
	//initial maximum HP at _lvl 1
	_maxHp = 10 + modifier;
	//HP gain for every subsequent _lvl
	for (int i = 1; i < lvl; i++) {
		levelUpHitPointGain();
	}
}

//! All ability modifiers (str,dex,con,int,wis,cha) are updated here, along with damage bonus and armor class
void Character::updateModifiersAndBonuses() {
	//setting/re-setting ability modifiers...
	_strengthModifier = abilityModifier(_abilityScores[0]);
	_dexterityModifier = abilityModifier(_abilityScores[1]);
	_constitutionModifier = abilityModifier(_abilityScores[2]);
	_intelligenceModifier = abilityModifier(_abilityScores[3]);
	_wisdomModifier = abilityModifier(_abilityScores[4]);
	_charismaModifier = abilityModifier(_abilityScores[5]);

	_damageBonus = _strengthModifier;
	updateAttackBonus();

	//notifying CharacterObserver of changes
	notify();
}

//! Function to randomly generate the increase in hit points per _lvl
//! Based on the hit die rule as described above, the fighter's hit die is 1d10
//! Can't add to max HP any value under 0, as it would not make any sense to have a lower maximum hit point pool simply from gaining experience
void Character::levelUpHitPointGain() {
	// _hp initially set to -1 to show that character is still being created (see in setInitialMaxHP() function)
	// thus signaling there is no need to print max HP increase
	if (!(_hp == (-1)))
		std::cout << "Max hit points have increased by ";
	std::string conModifier;
	if (_constitutionModifier >= 0) {
		conModifier = "+" + std::to_string(_constitutionModifier);
	}
	else conModifier = std::to_string(_constitutionModifier);
	int gain = Dice::roll("d10" + conModifier);
	if (gain < 0) {
		// _hp initially set to -1 to show that character is still being created (see in setInitialMaxHP() function)
		// thus signaling there is no need to print max HP increase
		if (!(_hp == (-1) ))
			std::cout << "0 (" << std::to_string(_maxHp) << "->" << std::to_string(_maxHp) << ")." << std::endl;
		gain = 0;
	}
	// _hp initially set to -1 to show that character is still being created (see in setInitialMaxHP() function)
	// thus signaling there is no need to print max HP increase
	if (!(_hp == (-1)))
		std::cout << gain << " (" << std::to_string(_maxHp) << "->" << std::to_string((_maxHp + gain)) << ")" << std::endl;
	_maxHp += gain;
}

//! Function to get various ability modifiers based on the ability entered
//! From the D&D Player's Handbook: "To determine an ability modifier without consulting the table, subtract 10 from the ability score and then divide the total by 2 (round down)."
//! @param attribute: The attribute on which the ability modifier is based
//! @return an ability modifier based on the attribute entered in its parameter.
int Character::abilityModifier(double attribute) {
	return (floor((attribute - 10) / 2));
}

//! updating base attack bonus for fighter class (https://www.dandwiki.com/wiki/SRD:Fighter)
void Character::updateBaseAttackBonus() {
	//re-setting base attack bonus to 0
	for (int i = 0; i < 4; i++) {
		_baseAttackBonus[i] = 0;
	}
	//first attack re-initializing
	for (int i = 0; ((i<_lvl) && (i<20)); i++) {
		_baseAttackBonus[0]++;
	}
	//second attack re-initializing
	for (int i = 5; ((i<_lvl) && (i<20)); i++) {
		_baseAttackBonus[1]++;
	}
	//third attack re-initializing
	for (int i = 10; ((i<_lvl) && (i<20)); i++) {
		_baseAttackBonus[2]++;
	}
	//fourth attack re-initializing
	for (int i = 15; ((i<_lvl) && (i<20)); i++) {
		_baseAttackBonus[3]++;
	}
	updateAttackBonus();
}

//! Function to get the Character's attack bonus, based on the base attack bonus and type of _weapon of the Character.
//! @return (_lvl + _strengthModifier): If weapon is melee
//! @return (_lvl + _dexterityModifier): If weapon is ranged
void Character::updateAttackBonus() {
	//re-setting attack bonus to 0
	for (int i = 0; i < 4; i++) {
		_attackBonus[i] = 0;
	}
	//updating attack bonus
	//NULL would mean no weapons, leaving the character with only fists to attack with
	if (_weapon == NULL)
		for (int i = 0; i < 4; i++) {
			_attackBonus[i] = _baseAttackBonus[i] + _strengthModifier;
		}
	else {
		int enchValue = 0;
		std::vector<Enchant*> enchants = _weapon->getEnchants();
		for (unsigned int i = 0; i < enchants.size(); i++) {
			if (enchants[i]->getType() == ATK)
				enchValue += enchants[i]->getValue();
		}
		if (_weapon->getRange() == 0) {
			for (unsigned int i = 0; i < 4; i++) {
				_attackBonus[i] = _baseAttackBonus[i] + _strengthModifier + enchValue;
			}
		}
		else {
			for (unsigned int i = 0; i < 4; i++) {
				_attackBonus[i] = _baseAttackBonus[i] + _dexterityModifier + enchValue;
			}
		}
	}
}

//! Implementation of the verification of a newly created Character
//! @return bool value, true of the character is valid (Stat should be in the 3-18 range for a new character), false if invalid. 
bool Character::validateNewCharacter() {
	for (int i = 0; i <= 5; i++)
		if (_abilityScores[i]<3 || _abilityScores[i]>18)
			return false;
	return true;
}

//! verification for a newly created non-player character, conditions are more lax than player character as NPCs cover anything from rats to gods
//! @return bool value, true if the character is valid (Stat should be at least 1 each), false if invalid. 
bool Character::validateNewNPC() {
	for (int i = 0; i <= 5; i++) {
		if (_abilityScores[i] < 1)
			return false;
	}
	return true;
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param damage: damage sustained by the character
void Character::hit(int damage) {
	_hp -= damage;
	if (_hp < 1)
		_isAlive = false;
	//notifying CharacterObserver of changes
	notify();
}

//! Function to print out the Character's Stat, attributes, and all the info stored in a nice and pretty way
void Character::printStat() {
	std::cout << "\n\n== CHARACTER SHEET ==" << std::endl;
	std::cout << "NAME: " << getName() << std::endl;
	std::cout << "STATUS: " << (_isAlive ? "Alive" : "Dead") << std::endl;
	std::cout << "CLASS: " << getClass() << std::endl;
	std::cout << "LEVEL: " << getLevel() << std::endl;
	std::cout << "EXP: " << getExpPoints() << std::endl;
	std::cout << "HIT POINTS: " << getCurrentHitPoints() << " out of " << getMaxHitPoints() << std::endl;
	std::cout << "STR: " << getStrength() << " (modifier: " << getStrengthModifier() << ")" << std::endl;
	std::cout << "DEX: " << getDexterity() << " (modifier: " << getDexterityModifier() << ")" << std::endl;
	std::cout << "CON: " << getConstitution() << " (modifier: " << getConstitutionModifier() << ")" << std::endl;
	std::cout << "INT: " << getIntelligence() << " (modifier: " << getIntelligenceModifier() << ")" << std::endl;
	std::cout << "WIS: " << getWisdom() << " (modifier: " << getWisdomModifier() << ")" << std::endl;
	std::cout << "CHA: " << getCharisma() << " (modifier: " << getCharismaModifier() << ")" << std::endl;
	std::cout << "ARMOR CLASS: " << getArmorClass() << std::endl;
	//printing base attack bonus
	std::cout << "BASE ATTACK BONUS: " << "+" << getBaseAttackBonus(0);
	if (_lvl > 5)
		std::cout << "/+" << getBaseAttackBonus(1);
	if (_lvl > 10)
		std::cout << "/+" << getBaseAttackBonus(2);
	if (_lvl > 15)
		std::cout << "/+" << getBaseAttackBonus(3);
	std::cout << std::endl;
	//printing attack bonus
	std::cout << "ATTACK BONUS: " << ((getAttackBonus(0) > (-1)) ? "+" : "") << getAttackBonus(0);
	if (_lvl > 5)
		std::cout << ((getAttackBonus(1) > (-1)) ? "/+" : "/") << getAttackBonus(1);
	if (_lvl > 10)
		std::cout << ((getAttackBonus(2) > (-1)) ? "/+" : "/") << getAttackBonus(2);
	if (_lvl > 15)
		std::cout << ((getAttackBonus(3) > (-1)) ? "/+" : "/") << getAttackBonus(3);
	std::cout << std::endl;
	std::cout << "DAMAGE BONUS: " << getDamageBonus() << std::endl;
	std::cout << std::endl;
	printEquippedItems();
	std::cout << std::endl;
	_backpack->printContents();
	std::cout << "\n\n" << std::endl;
}

//! Function to print out the character's worn equipment
void Character::printEquippedItems() {
	std::cout << "EQUIPPED" << std::endl;
	std::cout << "========" << std::endl;
	//printing weapon
	std::cout << "WEAPON: ";
	if (!(_weapon == NULL))
		std::cout << _weapon->getName() << " (TYPE: " << _weapon->getSubtype() << ")" << std::endl;
	else std::cout << "None (TYPE: Melee)" << std::endl;
	//printing shield
	std::cout << "SHIELD: ";
	if (!(_equipment[0] == NULL))
		std::cout << _equipment[0]->getName() << std::endl;
	else std::cout << "None" << std::endl;
	//printing helmet
	std::cout << "HELMET: ";
	if (!(_equipment[1] == NULL))
		std::cout << _equipment[1]->getName() << std::endl;
	else std::cout << "None" << std::endl;
	//printing armor
	std::cout << "ARMOR: ";
	if (!(_equipment[2] == NULL))
		std::cout << _equipment[2]->getName() << std::endl;
	else std::cout << "None" << std::endl;
	//printing belt
	std::cout << "BELT: ";
	if (!(_equipment[3] == NULL))
		std::cout << (*_equipment[3]).getName() << std::endl;
	else std::cout << "None" << std::endl;
	//printing boots
	std::cout << "BOOTS: ";
	if (!(_equipment[4] == NULL))
		std::cout << _equipment[4]->getName() << std::endl;
	else std::cout << "None" << std::endl;
	//printing ring
	std::cout << "RING: ";
	if (!(_equipment[5] == NULL))
		std::cout << _equipment[5]->getName() << std::endl;
	else std::cout << "None" << std::endl;
}

// FROM ROBERT: Code below is Charles' part. Commenting this out, as this is not relevant to my assignment submission
// rescale character to desired _lvl
// @param tgt_lvl : target _lvl to rescale to
void Character::rescale(int tgt_lvl)
{
	_lvl = tgt_lvl;

	_xp = 0;
	int lev_temp = _lvl;
	while (lev_temp > 1) {
		_xp += (lev_temp - 1) * 1000;
		lev_temp--;
	}
	updateBaseAttackBonus();

	//reset all ability scores to lvl 1 value
	for (int i = 0; i < 6; i++)
	{
		_abilityScores[i] = 12;
	}

	//bonus points to assign, one every 4 _lvls
	int bonus_attr = tgt_lvl / 4;

	//assign all to STR
	_abilityScores[0] += bonus_attr;

	//modifiers
	_strengthModifier = abilityModifier(_abilityScores[0]);
	_dexterityModifier = abilityModifier(_abilityScores[1]);
	_constitutionModifier = abilityModifier(_abilityScores[2]);
	_intelligenceModifier = abilityModifier(_abilityScores[3]);
	_wisdomModifier = abilityModifier(_abilityScores[4]);
	_charismaModifier = abilityModifier(_abilityScores[5]);
	_armorClass += 10 + _dexterityModifier;

	//setting hit points
	setInitialMaxHP(tgt_lvl, _constitutionModifier);
	_hp = _maxHp;

	//rescale _equipment Items
	if (_weapon)
	{
		_weapon->rescale(tgt_lvl);
	}

	for (int i = 0; i < 6; i++)
	{
		if (_equipment[i])
		{
			_equipment[i]->rescale(tgt_lvl);
		}
	}

	_damageBonus = _strengthModifier;
	updateAttackBonus();
}

//! function for receiving experience points, character _lvls up accordingly.
//! @param i: amount of experience pts gained
void Character::gainExp(int i) {
	//adds i onto current xp point pool
	_xp += i;
	int newLvlTemp = 2, newLvlMinReqExp = 1000;
	//checks for what the new _lvl will be after xp gain
	while (true) {
		if (_xp < newLvlMinReqExp) {
			break;
		}
		else {
			newLvlMinReqExp += (newLvlTemp) * 1000;
			newLvlTemp++;
		}
	}
	//output into terminal for each _lvl-up
	while (_lvl < (newLvlTemp - 1)) {
		std::cout << "\nYou have _lvled up: " << _lvl << "->" << (_lvl + 1) << std::endl;
		_lvl++;
		//note for later: any _lvl-up related functions can be called here
		levelUpHitPointGain();
	}
	updateBaseAttackBonus();
	//notifying CharacterObserver of changes
	notify();
}

//! function for character action where a non-posession item is taken
//! @param it: item being taken
void Character::takeItem(Item* it) {
	_backpack->addItem(it);
	std::cout << "\"" << it->getName() << "\" has been taken." << std::endl;
	//notifying CharacterObserver of changes
	notify();
}

//! function for character action where an item in posession is _equipment
//! @param it: item being _equipment
void Character::equipItem(Item* it) {
	//retrieve item index
	int itemIndex = _backpack->getItemIndex(it);
	//checks if item exists in _backpack
	if (!(itemIndex == -1)) {
		//check if weapon or approproiate equipment type
		switch (it->getType()) {
		case ItemType::WEAPON:
			//unequip any current weapon
			unequipWeapon();
			//equip the item
			_weapon = static_cast<Weapon*>(_backpack->removeItem(itemIndex));
			//addWeaponEnch(_weapon);
			std::cout << "Weapon \"" << _weapon->getName() << "\" has been _equipment." << std::endl;
			updateModifiersAndBonuses();
			break;
		case ItemType::SHIELD:
			//unequip any current shield
			unequipItem(0);
			//equip the item
			_equipment[0] = static_cast<Equipment*>(_backpack->removeItem(itemIndex));
			addShieldEnchEffects(_equipment[0]);
			std::cout << "Shield \"" << _equipment[0]->getName() << "\" has been _equipment." << std::endl;
			updateModifiersAndBonuses();
			break;
		case ItemType::HELMET:
			//unequip any current helmet
			unequipItem(1);
			//equip the item
			_equipment[1] = static_cast<Equipment*>(_backpack->removeItem(itemIndex));
			addHelmetEnchEffects(_equipment[1]);
			std::cout << "Helmet \"" << _equipment[1]->getName() << "\" has been _equipment." << std::endl;
			updateModifiersAndBonuses();
			break;
		case ItemType::ARMOR:
			//unequip any current armor
			unequipItem(2);
			//equip the item
			_equipment[2] = static_cast<Equipment*>(_backpack->removeItem(itemIndex));
			addArmorEnchEffects(_equipment[2]);
			std::cout << "Armor \"" << _equipment[2]->getName() << "\" has been _equipment." << std::endl;
			updateModifiersAndBonuses();
			break;
		case ItemType::BELT:
			//unequip any current belt
			unequipItem(3);
			//equip the item
			_equipment[3] = static_cast<Equipment*>(_backpack->removeItem(itemIndex));
			addBeltEnchEffects(_equipment[3]);
			std::cout << "Belt \"" << _equipment[3]->getName() << "\" has been _equipment." << std::endl;
			updateModifiersAndBonuses();
			break;
		case ItemType::BOOTS:
			//unequip any current boots
			unequipItem(4);
			//equip the item
			_equipment[4] = static_cast<Equipment*>(_backpack->removeItem(itemIndex));
			addBootsEnchEffects(_equipment[4]);
			std::cout << "Boots \"" << _equipment[4]->getName() << "\" has been _equipment." << std::endl;
			updateModifiersAndBonuses();
			break;
		case ItemType::RING:
			//unequip any current ring
			unequipItem(5);
			//equip the item
			_equipment[5] = static_cast<Equipment*>(_backpack->removeItem(itemIndex));
			addRingEnchEffects(_equipment[5]);
			std::cout << "Ring \"" << _equipment[5]->getName() << "\" has been _equipment." << std::endl;
			updateModifiersAndBonuses();
			break;
		default:
			std::cout << "Item \"" << it->getName() << "\" cannot be _equipment." << std::endl;
			break;
		}
	}
	else
		std::cout << "You do not have \"" << it->getName() << "." << std::endl;
}

//! function for unequipping items: adds items back into the _backpack, and sets element at array index to point to null
//! @param i: index of item in _equipment[]
void Character::unequipItem(int i) {
	//checks if the index is within range
	if ((i > -1) && (i < 6)) {
		//checks if there's anything to unequip in the first place
		if (!(_equipment[i] == NULL)) {
			//removing item's enchantments
			switch (i) {
				case 0:
					removeShieldEnchEffects(_equipment[i]);
					break;
				case 1:
					removeHelmetEnchEffects(_equipment[i]);
					break;
				case 2:
					removeArmorEnchEffects(_equipment[i]);
					break;
				case 3:
					removeBeltEnchEffects(_equipment[i]);
					break;
				case 4:
					removeBootsEnchEffects(_equipment[i]);
					break;
				case 5:
					removeRingEnchEffects(_equipment[i]);
					break;
				default:
					std::cout << "Error" << std::endl;
					break;
			}
			_backpack->addItem(_equipment[i]);
		}
		_equipment[i] = NULL;
		updateModifiersAndBonuses();
		//notifying CharacterObserver of changes
		notify();
	}
}
//! function for unequipping currently worn shield
void Character::unequipShield() { unequipItem(0); }

//! function for unequipping currently worn helmet
void Character::unequipHelmet() { unequipItem(1); }

//! function for unequipping currently worn armor
void Character::unequipArmor() { unequipItem(2); }

//! function for unequipping currently worn belt
void Character::unequipBelt() { unequipItem(3); }

//! function for unequipping currently worn boots
void Character::unequipBoots() { unequipItem(4); }

//! function for unequipping currently worn ring
void Character::unequipRing() { unequipItem(5); }

//! function for unequipping currently _equipment weapon
void Character::unequipWeapon() {
	if (!(_weapon == NULL)) {
		removeWeaponEnchEffects(_weapon);
		_backpack->addItem(_weapon);
		_weapon = NULL;
	}
	//notifying CharacterObserver of changes
	notify();
}

//! function for removing a to-be-un_equipment weapon's enchantments
//! @param w: to-be-removed weapon
void Character::removeWeaponEnchEffects(Weapon* w) {
	std::vector<Enchant*> enchants = w->getEnchants();
	//removing damage attack bonus enchantment
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == ATK)
			for (int i = 0; i < 4; i++)
				_attackBonus[i] -= enchants[i]->getValue();
	}
	//removing damage bonus enchantment
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == DMG)
			_damageBonus -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-un_equipment shield's enchantments
//! @param e: to-be-removed shield
void Character::removeShieldEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//removing armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			_armorClass -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-un_equipment helmet's enchantments
//! @param e: to-be-removed helmet
void Character::removeHelmetEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//removing armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			_armorClass -= enchants[i]->getValue();
	}
	//removing intelligence enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == INT)
			_abilityScores[3] -= enchants[i]->getValue();
	}
	//removing wisdom enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == WIS)
			_abilityScores[4] -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-un_equipment armor's enchantments
//! @param e: to-be-removed armor
void Character::removeArmorEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//removing armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			_armorClass -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-un_equipment belt's enchantments
//! @param e: to-be-removed belt
void Character::removeBeltEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//removing constitution enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CON)
			_abilityScores[2] -= enchants[i]->getValue();
	}
	//removing strength enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			_abilityScores[0] -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-un_equipment boots's enchantments
//! @param e: to-be-removed boots
void Character::removeBootsEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//removing armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			_armorClass -= enchants[i]->getValue();
	}
	//removing dexterity enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			_abilityScores[1] -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-un_equipment ring's enchantments
//! @param e: to-be-removed ring
void Character::removeRingEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//removing armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			_armorClass -= enchants[i]->getValue();
	}
	//removing strength enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			_abilityScores[0] -= enchants[i]->getValue();
	}
	//removing constitution enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CON)
			_abilityScores[2] -= enchants[i]->getValue();
	}
	//removing wisdom enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == WIS)
			_abilityScores[4] -= enchants[i]->getValue();
	}
	//removing charisma enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CHA)
			_abilityScores[5] -= enchants[i]->getValue();
	}
}

void Character::addShieldEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//adding armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			_armorClass += enchants[i]->getValue();
	}
}
void Character::addHelmetEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//adding armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			_armorClass += enchants[i]->getValue();
	}
	//adding intelligence enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == INT)
			_abilityScores[3] += enchants[i]->getValue();
	}
	//adding wisdom enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == WIS)
			_abilityScores[4] += enchants[i]->getValue();
	}
}
void Character::addArmorEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//adding armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			_armorClass += enchants[i]->getValue();
	}
}
void Character::addBeltEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//adding constitution enhancement
	for (int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CON)
			_abilityScores[2] += enchants[i]->getValue();
	}
	//adding strength enhancement
	for (int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			_abilityScores[0] += enchants[i]->getValue();
	}
}
void Character::addBootsEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//adding armor class enhancement
	for (int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			_armorClass += enchants[i]->getValue();
	}
	//adding dexterity enhancement
	for (int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			_abilityScores[1] += enchants[i]->getValue();
	}
}
void Character::addRingEnchEffects(Equipment* e) {
	std::vector<Enchant*> enchants = e->getEnchants();
	//adding armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			_armorClass += enchants[i]->getValue();
	}
	//adding strength enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			_abilityScores[0] += enchants[i]->getValue();
	}
	//adding constitution enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CON)
			_abilityScores[2] += enchants[i]->getValue();
	}
	//adding wisdom enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == WIS)
			_abilityScores[4] += enchants[i]->getValue();
	}
	//adding charisma enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CHA)
			_abilityScores[5] += enchants[i]->getValue();
	}
}

//! function for removing an item located at index i in "contents" array in _backpack
//! @param i: index of item to be removed
//! @return droppedItem
Item* Character::dropItem(int i) {
	Item* droppedItem = _backpack->removeItem(i);
	//notifying CharacterObserver of changes
	std::cout << "Dropped item \"" << droppedItem->getName() << "\" from _backpack." << std::endl;
	notify();
	return droppedItem;
}

//! getter method for _name
//! @return _name

std::string Character::getName() {
	return _name;
}

//! getter method for _class
//! @return _class

std::string Character::getClass() {
	return _class;
}

//! getter method for _lvl
//! @return _lvl
int Character::getLevel() {
	return _lvl;
}
//! getter method for exp points
//! @return exp points
int Character::getExpPoints() {
	return _xp;
}
//! getter method for strength
//! @return strength
int Character::getStrength() {
	return _abilityScores[0];
}
//! getter method for dexterity
//! @return dexterity
int Character::getDexterity() {
	return _abilityScores[1];
}
//! getter method for constitution
//! @return constitution
int Character::getConstitution() {
	return _abilityScores[2];
}
//! getter method for intelligence
//! @return intelligence
int Character::getIntelligence() {
	return _abilityScores[3];
}
//! getter method for wisdom
//! @return wisdom
int Character::getWisdom() {
	return _abilityScores[4];
}
//! getter method for charisma
//! @return charisma
int Character::getCharisma() {
	return _abilityScores[5];
}
//! getter method for _maxHp
//! @return _maxHp
int Character::getMaxHitPoints() {
	return _maxHp;
}
//! getter method for _hp
//! @return _hp
int Character::getCurrentHitPoints() {
	return _hp;
}
//! getter method for _strengthModifier
//! @return _strengthModifier
int Character::getStrengthModifier() {
	return abilityModifier(getStrength());
}
//! getter method for _dexterityModifier
//! @return _dexterityModifier
int Character::getDexterityModifier() {
	return abilityModifier(getDexterity());
}
//! getter method for _constitutionModifier
//! @return _constitutionModifier
int Character::getConstitutionModifier() {
	return abilityModifier(getConstitution());
}
//! getter method for _intelligenceModifier
//! @return _intelligenceModifier
int Character::getIntelligenceModifier() {
	return abilityModifier(getIntelligence());
}
//! getter method for _wisdomModifier
//! @return _wisdomModifier
int Character::getWisdomModifier() {
	return abilityModifier(getWisdom());
}
//! getter method for _charismaModifier
//! @return _charismaModifier
int Character::getCharismaModifier() {
	return abilityModifier(getCharisma());
}
//! getter method for _armorClass
//! @return _armorClass
int Character::getArmorClass() {
	return _armorClass;
}
//! getter method for base attack bonus
//! @param i: attack number 1-4, represented by array indexes (i.e. 0 == attack #1)
//! return base attack bonus
int Character::getBaseAttackBonus(int i) {
	return _baseAttackBonus[i];
}
//! getter method for attack bonus
//! @param i: attack number 1-4, represented by array indexes (i.e. 0 == attack #1)
//! return attack bonus
int Character::getAttackBonus(int i) {
	return _attackBonus[i];
}
//! getter method for _damageBonus
//! @return damage bonus
int Character::getDamageBonus() {
	return _damageBonus;
}
ItemContainer* Character::getBackpack() {
	return _backpack;
}
//! getter method for _weapon
//! @return _weapon
Weapon* Character::getEquippedWeapon() {
	return _weapon;
}
//! getter method for _equipmentShield
//! @return _equipmentShield
Equipment* Character::getEquippedShield() {
	return _equipment[0];
}
//! getter method for _equipmentHelmet
//! @return _equipmentHelmet
Equipment* Character::getEquippedHelmet() {
	return _equipment[1];
}
//! getter method for _equipmentArmor
//! @return _equipmentArmor
Equipment* Character::getEquippedArmor() {
	return _equipment[2];
}
//! getter method for _equipmentBelt
//! @return _equipmentBelt
Equipment* Character::getEquippedBelt() {
	return _equipment[3];
}
//! getter method for _equipmentBoots
//! @return _equipmentBoots
Equipment* Character::getEquippedBoots() {
	return _equipment[4];
}
//! getter method for _equipmentRing
//! @return _equipmentRing
Equipment* Character::getEquippedRing() {
	return _equipment[5];
}

//! setter for character name
//! @param n: new name
void Character::setName(std::string n) {
	_name = n;
	//notifying CharacterObserver of changes
	notify();
}

//! setter for character class
//! @param c: new class
void Character::setClass(std::string c) {
	_class = c;
	//notifying CharacterObserver of changes
	notify();
}

//! setter method for character _lvl, also checks and sets xp points to the minimum amount required to be at that _lvl
//! source: http://ca.ign.com/wikis/dungeons-and-dragons/Level_and_XP_progression
//! @param i: new _lvl
void Character::setLevel(int i) {
	if (i > _lvl) {
		int lvl_temp = 1, min_exp_pts, new_exp_pts = 0;
		while (lvl_temp < i) {
			min_exp_pts = lvl_temp * 1000;
			new_exp_pts += min_exp_pts;
			lvl_temp++;
		}
		while (i > _lvl) {
			levelUpHitPointGain();
			_lvl++;
		}
		_xp = new_exp_pts;
		notify();
	}
	if (i < _lvl) {
		_lvl = i;
		// gives initial experience points based on new _lvl entered
		_xp = 0;
		while (i > 1) {
			_xp += (i - 1) * 1000;
			i--;
		}
		notify();
	}
}

//! setter method for exp pts, also checks and sets appropriate new _lvl based on it
//! source: http://ca.ign.com/wikis/dungeons-and-dragons/Level_and_XP_progression
//! @param i: new exp pts
void Character::setExpPoints(int i) {
	int new_lvl = 1, min_xp_to_next_lvl, exp_pts_temp = 0;

	if (i < _xp) {
		while (exp_pts_temp < i) {
			new_lvl++;
			min_xp_to_next_lvl = new_lvl * 1000;
			exp_pts_temp += min_xp_to_next_lvl;
		}
		_lvl = new_lvl;
		_xp = i;
	}
	if (i > _xp) {
		while (exp_pts_temp < i) {
			new_lvl++;
			if (new_lvl > _lvl) {
				//lvl up effects
				levelUpHitPointGain();
			}
			min_xp_to_next_lvl = new_lvl * 1000;
			exp_pts_temp += min_xp_to_next_lvl;
		}
		_lvl = new_lvl;
		_xp = i;
	}
	notify();
}

//! setter method for current hp, sets appropriate conditions & restrictions
//! if less than 1 hp = dead, current hp can't be more than max hp
//! @param i: new current hp
void Character::setCurrentHitPoints(int i) {
	if (i < 1) {
		_hp = i;
		_isAlive = false;
	}
	else if (i > _maxHp) {
		_hp = _maxHp;
	}
	else _hp = i;
	notify();
}

//! setter for strength
//! @param i: new strength value
void Character::setStrength(int i) {
	_abilityScores[0] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter for dexterity
//! @param i: new dexterity value
void Character::setDexterity(int i) {
	_abilityScores[1] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter for constitution
//! @param i: new constitution value
void Character::setConstitution(int i) {
	_abilityScores[2] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter for intelligence
//! @param n: new intelligence value
void Character::setIntelligence(int i) {
	_abilityScores[3] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter for wisdom
//! @param n: new wisdom value
void Character::setWisdom(int i) {
	_abilityScores[4] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter for charisma
//! @param n: new charisma value
void Character::setCharisma(int i) {
	_abilityScores[5] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter method for _weapon
//! @param w: The wanted Weapon to equip
void Character::setEquippedWeapon(Weapon* w) {
	_weapon = w;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for _equipmentShield
//! @param s: The wanted Shield to equip
void Character::setEquippedShield(Equipment* s) {
	_equipment[0] = s;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for _equipmentArmor
//! @param a: The wanted Weapon to equip
void Character::setEquippedArmor(Equipment* a) {
	_equipment[1] = a;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for _equipmentHelmet
//! @param h: The wanted Helmet to equip
void Character::setEquippedHelmet(Equipment* h) {
	_equipment[2] = h;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for _equipmentBoots
//! @param b: The wanted Boots to equip
void Character::setEquippedBoots(Equipment* b) {
	_equipment[3] = b;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for _equipmentBelt
//! @param b: The wanted Belt to equip
void Character::setEquippedBelt(Equipment* b) {
	_equipment[4] = b;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for _equipmentRing
//! @param r: The wanted Ring to equip
void Character::setEquippedRing(Equipment* r) {
	_equipment[5] = r;
	//notifying CharacterObserver of changes
	notify();
}