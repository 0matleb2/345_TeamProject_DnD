//!Implementation of the Character class.

#pragma once

#include <iostream>
#include <math.h>		//for floor()
#include "Character.h"
#include "Dice.h"   
#include "Item.h"

using namespace std;

//! Default constructor, will most likely not be used at all outside of testing purposes
Character::Character() {
	characterName = "UNNAMED CHARACTER";
	characterClass = "Fighter";
	level = 1;
	expPoints= 0;
	isAlive = true;
	updateBaseAttackBonus();

	abilityScores[0] = 12;
	abilityScores[1] = 12;
	abilityScores[2] = 12;
	abilityScores[3] = 12;
	abilityScores[4] = 12;
	abilityScores[5] = 12;

	strengthModifier = abilityModifier(abilityScores[0]);
	dexterityModifier = abilityModifier(abilityScores[1]);
	constitutionModifier = abilityModifier(abilityScores[2]);
	intelligenceModifier = abilityModifier(abilityScores[3]);
	wisdomModifier = abilityModifier(abilityScores[4]);
	charismaModifier = abilityModifier(abilityScores[5]);
	armorClass += 10 + dexterityModifier;

	//hit points
	setInitialMaxHP(level, abilityModifier(abilityScores[2]));		//abilityScores[2] is constitution
	currentHitPoints = maxHitPoints;
	//equipment
	equippedWeapon = new Weapon("Basic Sword", itemType::WEAPON, vector<Enchant*>(), 0, weaponType::MELEE);
	equipped[0] = new Equipment("Basic Shield", itemType::SHIELD, vector<Enchant*>());
	equipped[1] = new Equipment("Basic Helmet", itemType::HELMET, vector<Enchant*>());
	equipped[2] = new Equipment("Basic Armor", itemType::ARMOR, vector<Enchant*>());
	equipped[3] = new Equipment("Basic Belt", itemType::BELT, vector<Enchant*>());
	equipped[4] = new Equipment("Basic Boots", itemType::BOOTS, vector<Enchant*>());
	equipped[5] = new Equipment("Basic Ring", itemType::RING, vector<Enchant*>());
	backpack = new ItemContainer();
	updateModifiersAndBonuses();
}

//! Object constructor as per assignment instructions
//! @param charaClass: The wanted character class (Fighter is the only choice at the moment)
//! @param lvl: The wanted character level
//! All stats with the exception of attackBonus() are generated upon creation
Character::Character(string charaName,  string charaClass, int lvl) {
	characterName = charaName;
	characterClass = charaClass;
	level = lvl;
	isAlive = true;
	// gives initial experience points based on level entered
	expPoints = 0;
	int lev_temp = level;
	while (lev_temp > 1) {
		expPoints += (lev_temp - 1) * 1000;
		lev_temp--;
	}
	updateBaseAttackBonus();

	//rolling for initial stats
	vector<int> vec;
	// Rolls 4d20 and keeps the three highest rolls for each ability score
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			vec.push_back(Dice::roll("d6"));
		}
		std::sort(vec.begin(), vec.end());
		abilityScores[i] = (vec[0] + vec[1] + vec[2]);
		vec.clear();
	}

	strengthModifier = abilityModifier(abilityScores[0]);
	dexterityModifier = abilityModifier(abilityScores[1]);
	constitutionModifier = abilityModifier(abilityScores[2]);
	intelligenceModifier = abilityModifier(abilityScores[3]);
	wisdomModifier = abilityModifier(abilityScores[4]);
	charismaModifier = abilityModifier(abilityScores[5]);
	armorClass += 10 + dexterityModifier;

	//setting hit points
	setInitialMaxHP(level, constitutionModifier);
	currentHitPoints = maxHitPoints;

	//equipment
	equippedWeapon = new Weapon("Basic Sword", itemType::WEAPON, vector<Enchant*>(), 0, weaponType::MELEE);
	equipped[0] = new Equipment("Basic Shield", itemType::SHIELD, vector<Enchant*>());
	equipped[1] = new Equipment("Basic Helmet", itemType::HELMET, vector<Enchant*>());
	equipped[2] = new Equipment("Basic Armor", itemType::ARMOR, vector<Enchant*>());
	equipped[3] = new Equipment("Basic Belt", itemType::BELT, vector<Enchant*>());
	equipped[4] = new Equipment("Basic Boots", itemType::BOOTS, vector<Enchant*>());
	equipped[5] = new Equipment("Basic Ring", itemType::RING, vector<Enchant*>());
	backpack = new ItemContainer();

	damageBonus = strengthModifier;
	updateAttackBonus();
}

Character::Character(std::string name, std::string charaClass, int lvl, int str, int dex, int con, int intel, int wis, int cha) {
	characterName = name;
	characterClass = charaClass;
	level = lvl;
	isAlive = true;
	// gives initial experience points based on level entered
	expPoints = 0;
	int lev_temp = level;
	while (lev_temp > 1) {
		expPoints += (lev_temp - 1) * 1000;
		lev_temp--;
	}
	updateBaseAttackBonus();

	abilityScores[0] = str;
	abilityScores[1] = dex;
	abilityScores[2] = con;
	abilityScores[3] = intel;
	abilityScores[4] = wis;
	abilityScores[5] = cha;

	strengthModifier = abilityModifier(abilityScores[0]);
	dexterityModifier = abilityModifier(abilityScores[1]);
	constitutionModifier = abilityModifier(abilityScores[2]);
	intelligenceModifier = abilityModifier(abilityScores[3]);
	wisdomModifier = abilityModifier(abilityScores[4]);
	charismaModifier = abilityModifier(abilityScores[5]);
	armorClass += 10 + dexterityModifier;

	//setting hit points
	setInitialMaxHP(level, constitutionModifier);
	currentHitPoints = maxHitPoints;
	//equipment
	equippedWeapon = new Weapon("Basic Sword", itemType::WEAPON, vector<Enchant*>(), 0, weaponType::MELEE);
	equipped[0] = new Equipment("Basic Shield", itemType::SHIELD, vector<Enchant*>());
	equipped[1] = new Equipment("Basic Helmet", itemType::HELMET, vector<Enchant*>());
	equipped[2] = new Equipment("Basic Armor", itemType::ARMOR, vector<Enchant*>());
	equipped[3] = new Equipment("Basic Belt", itemType::BELT, vector<Enchant*>());
	equipped[4] = new Equipment("Basic Boots", itemType::BOOTS, vector<Enchant*>());
	equipped[5] = new Equipment("Basic Ring", itemType::RING, vector<Enchant*>());
	backpack = new ItemContainer();

	damageBonus = strengthModifier;
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
	characterName = "UNNAMED CHARACTER";
	characterClass = "Fighter";
	level = 1;
	isAlive = true;
	updateBaseAttackBonus();

	abilityScores[0] = str;
	abilityScores[1] = dex;
	abilityScores[2] = con;
	abilityScores[3] = intel;
	abilityScores[4] = wis;
	abilityScores[5] = cha;

	strengthModifier = abilityModifier(abilityScores[0]);
	dexterityModifier = abilityModifier(abilityScores[1]);
	constitutionModifier = abilityModifier(abilityScores[2]);
	intelligenceModifier = abilityModifier(abilityScores[3]);
	wisdomModifier = abilityModifier(abilityScores[4]);
	charismaModifier = abilityModifier(abilityScores[5]);
	armorClass += 10 + dexterityModifier;

	//hit points
	maxHitPoints = 10;
	currentHitPoints = 10;
	//equipment
	equippedWeapon = new Weapon("Basic Sword", itemType::WEAPON, vector<Enchant*>(), 0, weaponType::MELEE);
	equipped[0] = new Equipment("Basic Shield", itemType::SHIELD, vector<Enchant*>());
	equipped[1] = new Equipment("Basic Helmet", itemType::HELMET, vector<Enchant*>());
	equipped[2] = new Equipment("Basic Armor", itemType::ARMOR, vector<Enchant*>());
	equipped[3] = new Equipment("Basic Belt", itemType::BELT, vector<Enchant*>());
	equipped[4] = new Equipment("Basic Boots", itemType::BOOTS, vector<Enchant*>());
	equipped[5] = new Equipment("Basic Ring", itemType::RING, vector<Enchant*>());
	backpack = new ItemContainer();

	damageBonus = strengthModifier;
	updateAttackBonus();
}

//! copy constructor
Character::Character(const Character& orig) :
	characterName(orig.characterName),
	characterClass(orig.characterClass),
	level(orig.level),
	expPoints(orig.expPoints),
	maxHitPoints(orig.maxHitPoints),
	currentHitPoints(orig.currentHitPoints),
	isAlive(orig.isAlive),
	armorClass(orig.armorClass),
	damageBonus(orig.damageBonus),
	strengthModifier(orig.strengthModifier),
	dexterityModifier(orig.dexterityModifier),
	intelligenceModifier(orig.intelligenceModifier),
	wisdomModifier(orig.wisdomModifier),
	charismaModifier(orig.charismaModifier),
	constitutionModifier(orig.constitutionModifier)
{
	for (int i = 0; i < 6; i++) {
		abilityScores[i] = orig.abilityScores[i];
	}
	equippedWeapon = orig.equippedWeapon->clone();
	for (int i = 0; i < 6; i++) {
		equipped[i] = orig.equipped[i]->clone();
	}
	for (int i = 0; i < orig.backpack->getSize(); i++) {
		backpack->addItem(orig.backpack->getItem(i)->clone());
	}
	for (int i = 0; i < 4; i++) {
		baseAttackBonus[i] = orig.baseAttackBonus[i];
	}
	for (int i = 0; i < 4; i++) {
		attackBonus[i] = orig.attackBonus[i];
	}
}

//! Object destructor
Character::~Character() {
	
	delete equippedWeapon;
	equippedWeapon = NULL;

	for (int i = 0; i < 6; i++)	{
		delete equipped[i];
		equipped[i] = NULL;
	}

	delete backpack;
	backpack = NULL;

	cout << "Character object has been destroyed" << endl;
}

//! Function for giving max HP for a newly-created character.
//! Checks if a level higher than 1 was given at creation and adds more to the max hit point pool based on that
//! using the @levelUpHitPointGain() function. Every subsequent level generates a number between 1 and 10, plus constitutionModifier
void Character::setInitialMaxHP(int lvl, int modifier) {
	//currentHitPoints set to -1 initially to show to levelUpHitPointGain() function that the character is still being created,
	//as opposed to being already existent, thus it is unnecessary to print out any messages displaying all the HP gains (see in levelUpHitPointGain())
	currentHitPoints = -1;
	//initial maximum HP at level 1
	maxHitPoints = 10 + modifier;
	//HP gain for every subsequent level
	for (int i = 1; i < lvl; i++) {
		levelUpHitPointGain();
	}
}

//! All ability modifiers (str,dex,con,int,wis,cha) are updated here, along with damage bonus and armor class
void Character::updateModifiersAndBonuses() {
	//setting/re-setting ability modifiers...
	strengthModifier = abilityModifier(abilityScores[0]);
	dexterityModifier = abilityModifier(abilityScores[1]);
	constitutionModifier = abilityModifier(abilityScores[2]);
	intelligenceModifier = abilityModifier(abilityScores[3]);
	wisdomModifier = abilityModifier(abilityScores[4]);
	charismaModifier = abilityModifier(abilityScores[5]);

	damageBonus = strengthModifier;
	updateAttackBonus();

	//notifying CharacterObserver of changes
	notify();
}

//! Function to randomly generate the increase in hit points per level
//! Based on the hit die rule as described above, the fighter's hit die is 1d10
//! Can't add to max HP any value under 0, as it would not make any sense to have a lower maximum hit point pool simply from gaining experience
void Character::levelUpHitPointGain() {
	// currentHitPoints initially set to -1 to show that character is still being created (see in setInitialMaxHP() function)
	// thus signaling there is no need to print max HP increase
	if (!(currentHitPoints == (-1)))
		std::cout << "Max hit points have increased by ";
	std::string conModifier;
	if (constitutionModifier >= 0) {
		conModifier = "+" + std::to_string(constitutionModifier);
	}
	else conModifier = std::to_string(constitutionModifier);
	int gain = Dice::roll("d10" + conModifier);
	if (gain < 0) {
		// currentHitPoints initially set to -1 to show that character is still being created (see in setInitialMaxHP() function)
		// thus signaling there is no need to print max HP increase
		if (!(currentHitPoints == (-1) ))
			cout << "0 (" << std::to_string(maxHitPoints) << "->" << std::to_string(maxHitPoints) << ")." << endl;
		gain = 0;
	}
	// currentHitPoints initially set to -1 to show that character is still being created (see in setInitialMaxHP() function)
	// thus signaling there is no need to print max HP increase
	if (!(currentHitPoints == (-1)))
		cout << gain << " (" << std::to_string(maxHitPoints) << "->" << std::to_string((maxHitPoints + gain)) << ")" << endl;
	maxHitPoints += gain;
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
		baseAttackBonus[i] = 0;
	}
	//first attack re-initializing
	for (int i = 0; ((i<level) && (i<20)); i++) {
		baseAttackBonus[0]++;
	}
	//second attack re-initializing
	for (int i = 5; ((i<level) && (i<20)); i++) {
		baseAttackBonus[1]++;
	}
	//third attack re-initializing
	for (int i = 10; ((i<level) && (i<20)); i++) {
		baseAttackBonus[2]++;
	}
	//fourth attack re-initializing
	for (int i = 15; ((i<level) && (i<20)); i++) {
		baseAttackBonus[3]++;
	}
	updateAttackBonus();
}

//! Function to get the Character's attack bonus, based on the base attack bonus and type of equippedWeapon of the Character.
//! @return (level + strengthModifier): If weapon is melee
//! @return (level + dexterityModifier): If weapon is ranged
void Character::updateAttackBonus() {
	//re-setting attack bonus to 0
	for (int i = 0; i < 4; i++) {
		attackBonus[i] = 0;
	}
	//updating attack bonus
	//NULL would mean no weapons, leaving the character with only fists to attack with
	if (equippedWeapon == NULL)
		for (int i = 0; i < 4; i++) {
			attackBonus[i] = baseAttackBonus[i] + strengthModifier;
		}
	else {
		int enchValue = 0;
		vector<Enchant*> enchants = equippedWeapon->getEnch();
		for (unsigned int i = 0; i < enchants.size(); i++) {
			if (enchants[i]->getType() == ATK)
				enchValue += enchants[i]->getValue();
		}
		if (equippedWeapon->getRange() == 0) {
			for (unsigned int i = 0; i < 4; i++) {
				attackBonus[i] = baseAttackBonus[i] + strengthModifier + enchValue;
			}
		}
		else {
			for (unsigned int i = 0; i < 4; i++) {
				attackBonus[i] = baseAttackBonus[i] + dexterityModifier + enchValue;
			}
		}
	}
}

//! Implementation of the verification of a newly created Character
//! @return bool value, true of the character is valid (stats should be in the 3-18 range for a new character), false if invalid. 
bool Character::validateNewCharacter() {
	for (int i = 0; i <= 5; i++)
		if (abilityScores[i]<3 || abilityScores[i]>18)
			return false;
	return true;
}

//! verification for a newly created non-player character, conditions are more lax than player character as NPCs cover anything from rats to gods
//! @return bool value, true if the character is valid (stats should be at least 1 each), false if invalid. 
bool Character::validateNewNPC() {
	for (int i = 0; i <= 5; i++) {
		if (abilityScores[i] < 1)
			return false;
	}
	return true;
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param damage: damage sustained by the character
void Character::hit(int damage) {
	currentHitPoints -= damage;
	if (currentHitPoints < 1)
		isAlive = false;
	//notifying CharacterObserver of changes
	notify();
}

//! Function to print out the Character's stats, attributes, and all the info stored in a nice and pretty way
void Character::printStats() {
	cout << "\n\n== CHARACTER SHEET ==" << endl;
	cout << "NAME: " << getCharacterName() << endl;
	cout << "STATUS: " << (isAlive ? "Alive" : "Dead") << endl;
	cout << "CLASS: " << getCharacterClass() << endl;
	cout << "LEVEL: " << getLevel() << endl;
	cout << "EXP: " << getExpPoints() << endl;
	cout << "HIT POINTS: " << getCurrentHitPoints() << " out of " << getMaxHitPoints() << endl;
	cout << "STR: " << getStrength() << " (modifier: " << getStrengthModifier() << ")" << endl;
	cout << "DEX: " << getDexterity() << " (modifier: " << getDexterityModifier() << ")" << endl;
	cout << "CON: " << getConstitution() << " (modifier: " << getConstitutionModifier() << ")" << endl;
	cout << "INT: " << getIntelligence() << " (modifier: " << getIntelligenceModifier() << ")" << endl;
	cout << "WIS: " << getWisdom() << " (modifier: " << getWisdomModifier() << ")" << endl;
	cout << "CHA: " << getCharisma() << " (modifier: " << getCharismaModifier() << ")" << endl;
	cout << "ARMOR CLASS: " << getArmorClass() << endl;
	//printing base attack bonus
	cout << "BASE ATTACK BONUS: " << "+" << getBaseAttackBonus(0);
	if (level > 5)
		cout << "/+" << getBaseAttackBonus(1);
	if (level > 10)
		cout << "/+" << getBaseAttackBonus(2);
	if (level > 15)
		cout << "/+" << getBaseAttackBonus(3);
	cout << endl;
	//printing attack bonus
	cout << "ATTACK BONUS: " << ((getAttackBonus(0) > (-1)) ? "+" : "") << getAttackBonus(0);
	if (level > 5)
		cout << ((getAttackBonus(1) > (-1)) ? "/+" : "/") << getAttackBonus(1);
	if (level > 10)
		cout << ((getAttackBonus(2) > (-1)) ? "/+" : "/") << getAttackBonus(2);
	if (level > 15)
		cout << ((getAttackBonus(3) > (-1)) ? "/+" : "/") << getAttackBonus(3);
	cout << endl;
	cout << "DAMAGE BONUS: " << getDamageBonus() << endl;
	cout << endl;
	printEquippedItems();
	cout << endl;
	backpack->printContents();
	cout << "\n\n" << endl;
}

//! Function to print out the character's worn equipment
void Character::printEquippedItems() {
	cout << "EQUIPPED" << endl;
	cout << "========" << endl;
	//printing weapon
	cout << "WEAPON: ";
	if (!(equippedWeapon == NULL))
		cout << equippedWeapon->getName() << " (TYPE: " << equippedWeapon->getSubtype() << ")" << endl;
	else cout << "None (TYPE: Melee)" << endl;
	//printing shield
	cout << "SHIELD: ";
	if (!(equipped[0] == NULL))
		cout << equipped[0]->getName() << endl;
	else cout << "None" << endl;
	//printing helmet
	cout << "HELMET: ";
	if (!(equipped[1] == NULL))
		cout << equipped[1]->getName() << endl;
	else cout << "None" << endl;
	//printing armor
	cout << "ARMOR: ";
	if (!(equipped[2] == NULL))
		cout << equipped[2]->getName() << endl;
	else cout << "None" << endl;
	//printing belt
	cout << "BELT: ";
	if (!(equipped[3] == NULL))
		cout << (*equipped[3]).getName() << endl;
	else cout << "None" << endl;
	//printing boots
	cout << "BOOTS: ";
	if (!(equipped[4] == NULL))
		cout << equipped[4]->getName() << endl;
	else cout << "None" << endl;
	//printing ring
	cout << "RING: ";
	if (!(equipped[5] == NULL))
		cout << equipped[5]->getName() << endl;
	else cout << "None" << endl;
}

// FROM ROBERT: Code below is Charles' part. Commenting this out, as this is not relevant to my assignment submission
// rescale character to desired level
// @param tgt_lvl : target level to rescale to
void Character::rescale(int tgt_lvl)
{
	level = tgt_lvl;

	expPoints = 0;
	int lev_temp = level;
	while (lev_temp > 1) {
		expPoints += (lev_temp - 1) * 1000;
		lev_temp--;
	}
	updateBaseAttackBonus();

	//reset all ability scores to lvl 1 value
	for (int i = 0; i < 6; i++)
	{
		abilityScores[i] = 12;
	}

	//bonus points to assign, one every 4 levels
	int bonus_attr = tgt_lvl / 4;

	//assign all to STR
	abilityScores[0] += bonus_attr;

	//modifiers
	strengthModifier = abilityModifier(abilityScores[0]);
	dexterityModifier = abilityModifier(abilityScores[1]);
	constitutionModifier = abilityModifier(abilityScores[2]);
	intelligenceModifier = abilityModifier(abilityScores[3]);
	wisdomModifier = abilityModifier(abilityScores[4]);
	charismaModifier = abilityModifier(abilityScores[5]);
	armorClass += 10 + dexterityModifier;

	//setting hit points
	setInitialMaxHP(tgt_lvl, constitutionModifier);
	currentHitPoints = maxHitPoints;

	//rescale equipped Items
	if (equippedWeapon)
	{
		equippedWeapon->rescale(tgt_lvl);
	}

	for (int i = 0; i < 6; i++)
	{
		if (equipped[i])
		{
			equipped[i]->rescale(tgt_lvl);
		}
	}

	damageBonus = strengthModifier;
	updateAttackBonus();
}

//! function for receiving experience points, character levels up accordingly.
//! @param i: amount of experience pts gained
void Character::gainExp(int i) {
	//adds i onto current xp point pool
	expPoints += i;
	int newLvlTemp = 2, newLvlMinReqExp = 1000;
	//checks for what the new level will be after xp gain
	while (true) {
		if (expPoints < newLvlMinReqExp) {
			break;
		}
		else {
			newLvlMinReqExp += (newLvlTemp) * 1000;
			newLvlTemp++;
		}
	}
	//output into terminal for each level-up
	while (level < (newLvlTemp - 1)) {
		cout << "\nYou have leveled up: " << level << "->" << (level + 1) << endl;
		level++;
		//note for later: any level-up related functions can be called here
		levelUpHitPointGain();
	}
	updateBaseAttackBonus();
	//notifying CharacterObserver of changes
	notify();
}

//! function for character action where a non-posession item is taken
//! @param it: item being taken
void Character::takeItem(Item* it) {
	backpack->addItem(it);
	cout << "\"" << it->getName() << "\" has been taken." << endl;
	//notifying CharacterObserver of changes
	notify();
}

//! function for character action where an item in posession is equipped
//! @param it: item being equipped
void Character::equipItem(Item* it) {
	//retrieve item index
	int itemIndex = backpack->getItemIndex(it);
	//checks if item exists in backpack
	if (!(itemIndex == -1)) {
		//check if weapon or approproiate equipment type
		switch (it->getType()) {
		case itemType::WEAPON:
			//unequip any current weapon
			unequipWeapon();
			//equip the item
			equippedWeapon = static_cast<Weapon*>(backpack->removeItem(itemIndex));
			//addWeaponEnch(equippedWeapon);
			cout << "Weapon \"" << equippedWeapon->getName() << "\" has been equipped." << endl;
			updateModifiersAndBonuses();
			break;
		case itemType::SHIELD:
			//unequip any current shield
			unequipItem(0);
			//equip the item
			equipped[0] = static_cast<Equipment*>(backpack->removeItem(itemIndex));
			addShieldEnchEffects(equipped[0]);
			cout << "Shield \"" << equipped[0]->getName() << "\" has been equipped." << endl;
			updateModifiersAndBonuses();
			break;
		case itemType::HELMET:
			//unequip any current helmet
			unequipItem(1);
			//equip the item
			equipped[1] = static_cast<Equipment*>(backpack->removeItem(itemIndex));
			addHelmetEnchEffects(equipped[1]);
			cout << "Helmet \"" << equipped[1]->getName() << "\" has been equipped." << endl;
			updateModifiersAndBonuses();
			break;
		case itemType::ARMOR:
			//unequip any current armor
			unequipItem(2);
			//equip the item
			equipped[2] = static_cast<Equipment*>(backpack->removeItem(itemIndex));
			addArmorEnchEffects(equipped[2]);
			cout << "Armor \"" << equipped[2]->getName() << "\" has been equipped." << endl;
			updateModifiersAndBonuses();
			break;
		case itemType::BELT:
			//unequip any current belt
			unequipItem(3);
			//equip the item
			equipped[3] = static_cast<Equipment*>(backpack->removeItem(itemIndex));
			addBeltEnchEffects(equipped[3]);
			cout << "Belt \"" << equipped[3]->getName() << "\" has been equipped." << endl;
			updateModifiersAndBonuses();
			break;
		case itemType::BOOTS:
			//unequip any current boots
			unequipItem(4);
			//equip the item
			equipped[4] = static_cast<Equipment*>(backpack->removeItem(itemIndex));
			addBootsEnchEffects(equipped[4]);
			cout << "Boots \"" << equipped[4]->getName() << "\" has been equipped." << endl;
			updateModifiersAndBonuses();
			break;
		case itemType::RING:
			//unequip any current ring
			unequipItem(5);
			//equip the item
			equipped[5] = static_cast<Equipment*>(backpack->removeItem(itemIndex));
			addRingEnchEffects(equipped[5]);
			cout << "Ring \"" << equipped[5]->getName() << "\" has been equipped." << endl;
			updateModifiersAndBonuses();
			break;
		default:
			cout << "Item \"" << it->getName() << "\" cannot be equipped." << endl;
			break;
		}
	}
	else
		cout << "You do not have \"" << it->getName() << "." << endl;
}

//! function for unequipping items: adds items back into the backpack, and sets element at array index to point to null
//! @param i: index of item in equipped[]
void Character::unequipItem(int i) {
	//checks if the index is within range
	if ((i > -1) && (i < 6)) {
		//checks if there's anything to unequip in the first place
		if (!(equipped[i] == NULL)) {
			//removing item's enchantments
			switch (i) {
				case 0:
					removeShieldEnchEffects(equipped[i]);
					break;
				case 1:
					removeHelmetEnchEffects(equipped[i]);
					break;
				case 2:
					removeArmorEnchEffects(equipped[i]);
					break;
				case 3:
					removeBeltEnchEffects(equipped[i]);
					break;
				case 4:
					removeBootsEnchEffects(equipped[i]);
					break;
				case 5:
					removeRingEnchEffects(equipped[i]);
					break;
				default:
					cout << "Error" << endl;
					break;
			}
			backpack->addItem(equipped[i]);
		}
		equipped[i] = NULL;
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

//! function for unequipping currently equipped weapon
void Character::unequipWeapon() {
	if (!(equippedWeapon == NULL)) {
		removeWeaponEnchEffects(equippedWeapon);
		backpack->addItem(equippedWeapon);
		equippedWeapon = NULL;
	}
	//notifying CharacterObserver of changes
	notify();
}

//! function for removing a to-be-unequipped weapon's enchantments
//! @param w: to-be-removed weapon
void Character::removeWeaponEnchEffects(Weapon* w) {
	vector<Enchant*> enchants = w->getEnch();
	//removing damage attack bonus enchantment
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == ATK)
			for (int i = 0; i < 4; i++)
				attackBonus[i] -= enchants[i]->getValue();
	}
	//removing damage bonus enchantment
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == DMG)
			damageBonus -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-unequipped shield's enchantments
//! @param e: to-be-removed shield
void Character::removeShieldEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//removing armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			armorClass -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-unequipped helmet's enchantments
//! @param e: to-be-removed helmet
void Character::removeHelmetEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//removing armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			armorClass -= enchants[i]->getValue();
	}
	//removing intelligence enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == INT)
			abilityScores[3] -= enchants[i]->getValue();
	}
	//removing wisdom enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == WIS)
			abilityScores[4] -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-unequipped armor's enchantments
//! @param e: to-be-removed armor
void Character::removeArmorEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//removing armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			armorClass -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-unequipped belt's enchantments
//! @param e: to-be-removed belt
void Character::removeBeltEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//removing constitution enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CON)
			abilityScores[2] -= enchants[i]->getValue();
	}
	//removing strength enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			abilityScores[0] -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-unequipped boots's enchantments
//! @param e: to-be-removed boots
void Character::removeBootsEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//removing armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			armorClass -= enchants[i]->getValue();
	}
	//removing dexterity enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			abilityScores[1] -= enchants[i]->getValue();
	}
}

//! function for removing a to-be-unequipped ring's enchantments
//! @param e: to-be-removed ring
void Character::removeRingEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//removing armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			armorClass -= enchants[i]->getValue();
	}
	//removing strength enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			abilityScores[0] -= enchants[i]->getValue();
	}
	//removing constitution enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CON)
			abilityScores[2] -= enchants[i]->getValue();
	}
	//removing wisdom enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == WIS)
			abilityScores[4] -= enchants[i]->getValue();
	}
	//removing charisma enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CHA)
			abilityScores[5] -= enchants[i]->getValue();
	}
}

void Character::addShieldEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//adding armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			armorClass += enchants[i]->getValue();
	}
}
void Character::addHelmetEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//adding armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			armorClass += enchants[i]->getValue();
	}
	//adding intelligence enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == INT)
			abilityScores[3] += enchants[i]->getValue();
	}
	//adding wisdom enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == WIS)
			abilityScores[4] += enchants[i]->getValue();
	}
}
void Character::addArmorEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//adding armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			armorClass += enchants[i]->getValue();
	}
}
void Character::addBeltEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//adding constitution enhancement
	for (int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CON)
			abilityScores[2] += enchants[i]->getValue();
	}
	//adding strength enhancement
	for (int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			abilityScores[0] += enchants[i]->getValue();
	}
}
void Character::addBootsEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//adding armor class enhancement
	for (int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			armorClass += enchants[i]->getValue();
	}
	//adding dexterity enhancement
	for (int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			abilityScores[1] += enchants[i]->getValue();
	}
}
void Character::addRingEnchEffects(Equipment* e) {
	vector<Enchant*> enchants = e->getEnch();
	//adding armor class enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == AC)
			armorClass += enchants[i]->getValue();
	}
	//adding strength enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == STR)
			abilityScores[0] += enchants[i]->getValue();
	}
	//adding constitution enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CON)
			abilityScores[2] += enchants[i]->getValue();
	}
	//adding wisdom enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == WIS)
			abilityScores[4] += enchants[i]->getValue();
	}
	//adding charisma enhancement
	for (unsigned int i = 0; i < enchants.size(); i++) {
		if (enchants[i]->getType() == CHA)
			abilityScores[5] += enchants[i]->getValue();
	}
}

//! function for removing an item located at index i in "contents" array in backpack
//! @param i: index of item to be removed
//! @return droppedItem
Item* Character::dropItem(int i) {
	Item* droppedItem = backpack->removeItem(i);
	//notifying CharacterObserver of changes
	cout << "Dropped item \"" << droppedItem->getName() << "\" from backpack." << endl;
	notify();
	return droppedItem;
}

//! getter method for characterName
//! @return characterName
string Character::getCharacterName() {
	return characterName;
}

//! getter method for characterClass
//! @return characterClass
string Character::getCharacterClass() {
	return characterClass;
}

//! getter method for level
//! @return level
int Character::getLevel() {
	return level;
}
//! getter method for exp points
//! @return exp points
int Character::getExpPoints() {
	return expPoints;
}
//! getter method for strength
//! @return strength
int Character::getStrength() {
	return abilityScores[0];
}
//! getter method for dexterity
//! @return dexterity
int Character::getDexterity() {
	return abilityScores[1];
}
//! getter method for constitution
//! @return constitution
int Character::getConstitution() {
	return abilityScores[2];
}
//! getter method for intelligence
//! @return intelligence
int Character::getIntelligence() {
	return abilityScores[3];
}
//! getter method for wisdom
//! @return wisdom
int Character::getWisdom() {
	return abilityScores[4];
}
//! getter method for charisma
//! @return charisma
int Character::getCharisma() {
	return abilityScores[5];
}
//! getter method for maxHitPoints
//! @return maxHitPoints
int Character::getMaxHitPoints() {
	return maxHitPoints;
}
//! getter method for currentHitPoints
//! @return currentHitPoints
int Character::getCurrentHitPoints() {
	return currentHitPoints;
}
//! getter method for strengthModifier
//! @return strengthModifier
int Character::getStrengthModifier() {
	return abilityModifier(getStrength());
}
//! getter method for dexterityModifier
//! @return dexterityModifier
int Character::getDexterityModifier() {
	return abilityModifier(getDexterity());
}
//! getter method for wisdomModifier
//! @return wisdomModifier
int Character::getWisdomModifier() {
	return abilityModifier(getWisdom());
}
//! getter method for charismaModifier
//! @return charismaModifier
int Character::getCharismaModifier() {
	return abilityModifier(getCharisma());
}
//! getter method for constitutionModifier
//! @return constitutionModifier
int Character::getConstitutionModifier() {
	return abilityModifier(getConstitution());
}
//! getter method for intelligenceModifier
//! @return intelligenceModifier
int Character::getIntelligenceModifier() {
	return abilityModifier(getIntelligence());
}
//! getter method for armorClass
//! @return armorClass
int Character::getArmorClass() {
	return armorClass;
}
//! getter method for base attack bonus
//! @param i: attack number 1-4, represented by array indexes (i.e. 0 == attack #1)
//! return base attack bonus
int Character::getBaseAttackBonus(int i) {
	return baseAttackBonus[i];
}
//! getter method for attack bonus
//! @param i: attack number 1-4, represented by array indexes (i.e. 0 == attack #1)
//! return attack bonus
int Character::getAttackBonus(int i) {
	return attackBonus[i];
}
//! getter method for damageBonus
//! @return damage bonus
int Character::getDamageBonus() {
	return damageBonus;
}
ItemContainer* Character::getBackpack() {
	return backpack;
}
//! getter method for equippedWeapon
//! @return equippedWeapon
Weapon* Character::getEquippedWeapon() {
	return equippedWeapon;
}
//! getter method for equippedShield
//! @return equippedShield
Equipment* Character::getEquippedShield() {
	return equipped[0];
}
//! getter method for equippedHelmet
//! @return equippedHelmet
Equipment* Character::getEquippedHelmet() {
	return equipped[1];
}
//! getter method for equippedArmor
//! @return equippedArmor
Equipment* Character::getEquippedArmor() {
	return equipped[2];
}
//! getter method for equippedBelt
//! @return equippedBelt
Equipment* Character::getEquippedBelt() {
	return equipped[3];
}
//! getter method for equippedBoots
//! @return equippedBoots
Equipment* Character::getEquippedBoots() {
	return equipped[4];
}
//! getter method for equippedRing
//! @return equippedRing
Equipment* Character::getEquippedRing() {
	return equipped[5];
}

//! setter for character name
//! @param n: new name
void Character::setName(string n) {
	characterName = n;
	//notifying CharacterObserver of changes
	notify();
}

//! setter for character class
//! @param c: new class
void Character::setClass(string c) {
	characterClass = c;
	//notifying CharacterObserver of changes
	notify();
}

//! setter method for character level, also checks and sets xp points to the minimum amount required to be at that level
//! source: http://ca.ign.com/wikis/dungeons-and-dragons/Level_and_XP_progression
//! @param i: new level
void Character::setLevel(int i) {
	if (i > level) {
		int lvl_temp = 1, min_exp_pts, new_exp_pts = 0;
		while (lvl_temp < i) {
			min_exp_pts = lvl_temp * 1000;
			new_exp_pts += min_exp_pts;
			lvl_temp++;
		}
		while (i > level) {
			levelUpHitPointGain();
			level++;
		}
		expPoints = new_exp_pts;
		notify();
	}
	if (i < level) {
		level = i;
		// gives initial experience points based on new level entered
		expPoints = 0;
		while (i > 1) {
			expPoints += (i - 1) * 1000;
			i--;
		}
		notify();
	}
}

//! setter method for exp pts, also checks and sets appropriate new level based on it
//! source: http://ca.ign.com/wikis/dungeons-and-dragons/Level_and_XP_progression
//! @param i: new exp pts
void Character::setExpPoints(int i) {
	int new_lvl = 1, min_xp_to_next_lvl, exp_pts_temp = 0;

	if (i < expPoints) {
		while (exp_pts_temp < i) {
			new_lvl++;
			min_xp_to_next_lvl = new_lvl * 1000;
			exp_pts_temp += min_xp_to_next_lvl;
		}
		level = new_lvl;
		expPoints = i;
	}
	if (i > expPoints) {
		while (exp_pts_temp < i) {
			new_lvl++;
			if (new_lvl > level) {
				//lvl up effects
				levelUpHitPointGain();
			}
			min_xp_to_next_lvl = new_lvl * 1000;
			exp_pts_temp += min_xp_to_next_lvl;
		}
		level = new_lvl;
		expPoints = i;
	}
	notify();
}

//! setter method for current hp, sets appropriate conditions & restrictions
//! if less than 1 hp = dead, current hp can't be more than max hp
//! @param i: new current hp
void Character::setCurrentHitPoints(int i) {
	if (i < 1) {
		currentHitPoints = i;
		isAlive = false;
	}
	else if (i > maxHitPoints) {
		currentHitPoints = maxHitPoints;
	}
	else currentHitPoints = i;
	notify();
}

//! setter for strength
//! @param i: new strength value
void Character::setStrength(int i) {
	abilityScores[0] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter for dexterity
//! @param i: new dexterity value
void Character::setDexterity(int i) {
	abilityScores[1] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter for constitution
//! @param i: new constitution value
void Character::setConstitution(int i) {
	abilityScores[2] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter for intelligence
//! @param n: new intelligence value
void Character::setIntelligence(int i) {
	abilityScores[3] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter for wisdom
//! @param n: new wisdom value
void Character::setWisdom(int i) {
	abilityScores[4] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter for charisma
//! @param n: new charisma value
void Character::setCharisma(int i) {
	abilityScores[5] = i;
	updateModifiersAndBonuses();
	//notifying CharacterObserver of changes
	notify();
}

//! setter method for equippedWeapon
//! @param w: The wanted Weapon to equip
void Character::setEquippedWeapon(Weapon* w) {
	equippedWeapon = w;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for equippedShield
//! @param s: The wanted Shield to equip
void Character::setEquippedShield(Equipment* s) {
	equipped[0] = s;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for equippedArmor
//! @param a: The wanted Weapon to equip
void Character::setEquippedArmor(Equipment* a) {
	equipped[1] = a;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for equippedHelmet
//! @param h: The wanted Helmet to equip
void Character::setEquippedHelmet(Equipment* h) {
	equipped[2] = h;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for equippedBoots
//! @param b: The wanted Boots to equip
void Character::setEquippedBoots(Equipment* b) {
	equipped[3] = b;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for equippedBelt
//! @param b: The wanted Belt to equip
void Character::setEquippedBelt(Equipment* b) {
	equipped[4] = b;
	//notifying CharacterObserver of changes
	notify();
}
//! setter method for equippedRing
//! @param r: The wanted Ring to equip
void Character::setEquippedRing(Equipment* r) {
	equipped[5] = r;
	//notifying CharacterObserver of changes
	notify();
}