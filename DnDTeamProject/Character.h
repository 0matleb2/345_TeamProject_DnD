#pragma once

#include <string>
#include "Item.h"
#include "Equipment.h"
#include "Weapon.h"
#include "Dice.h"
#include "ItemContainer.h"
#include "Observable.h"

class Character: public Observable {

public:

	Character();
	Character(std::string, std::string, int);
	Character(int, int, int, int, int, int);
	Character(std::string name, std::string charaClass, int lvl, int str, int dex, int con, int intel, int wis, int cha);
	Character(const Character& original);
	~Character();

	std::string getName();
	std::string getClass();
	int getLevel();
	int getStrength();
	int getDexterity();
	int getConstitution();
	int getIntelligence();
	int getWisdom();
	int getCharisma();
	int getMaxHitPoints();
	int getCurrentHitPoints();
	int getExpPoints();
	int getStrengthModifier();
	int getDexterityModifier();
	int getConstitutionModifier();
	int getIntelligenceModifier();
	int getWisdomModifier();
	int getCharismaModifier();
	int getArmorClass();
	int getDamageBonus();
	int getBaseAttackBonus(int i);
	int getAttackBonus(int i);
	ItemContainer* getBackpack();
	Weapon* getEquippedWeapon();
	Equipment* getEquippedShield();
	Equipment* getEquippedHelmet();
	Equipment* getEquippedArmor();
	Equipment* getEquippedBelt();
	Equipment* getEquippedBoots();
	Equipment* getEquippedRing();

	void setName(std::string s);
	void setClass(std::string s);
	void setLevel(int i);
	void setExpPoints(int i);
	void setCurrentHitPoints(int i);
	void setStrength(int i);
	void setDexterity(int i);
	void setConstitution(int i);
	void setIntelligence(int i);
	void setWisdom(int i);
	void setCharisma(int i);
	void setEquippedWeapon(Weapon*);
	void setEquippedShield(Equipment*);
	void setEquippedHelmet(Equipment*);
	void setEquippedArmor(Equipment*);
	void setEquippedBelt(Equipment*);
	void setEquippedBoots(Equipment*);
	void setEquippedRing(Equipment*);

	bool validateNewCharacter();
	bool validateNewNPC();
	void printStats();
	void levelUpHitPointGain();
	void setInitialMaxHP(int lvl, int modifier);
	void hit(int);
	void gainExp(int i);

	void printEquippedItems();
	void takeItem(Item* i);
	Item* dropItem(int i);
	void equipItem(Item* e);
	void unequipItem(int i);
	void unequipWeapon();
	void unequipShield();
	void unequipHelmet();
	void unequipArmor();
	void unequipBelt();
	void unequipBoots();
	void unequipRing();

	void rescale(int tgt_lvl);

private:

	std::string _name;
	std::string _class;
	int _lvl;
	int _xp;
	int _abilityScores[6]; //str, dex, cons, int, wisd, char
	int _strengthModifier;
	int _dexterityModifier;
	int _constitutionModifier;
	int _intelligenceModifier;
	int _wisdomModifier;
	int _charismaModifier;
	int _maxHp;
	int _hp;
	bool _isAlive;
	int _armorClass;
	int _damageBonus;
	Weapon* _weapon;
	Equipment* _equipment[6]; //shield, helmet, armor, belt, boots, ring
	ItemContainer* _backpack;
	int _baseAttackBonus[4];
	int _attackBonus[4];



	void updateBaseAttackBonus();
	void updateAttackBonus();
	//Stats-setting & modifier updates (upon level-up or equipment change)
	int abilityModifier(double attribute);
	void updateModifiersAndBonuses();

	//adding enchantment effects from equipping items,
	//no addWeaponEnchEffects() because already covered by
	//updateModifiersAndBonuses() & updateAttackBonus()
	void addShieldEnchEffects(Equipment* e);
	void addHelmetEnchEffects(Equipment* e);
	void addArmorEnchEffects(Equipment* e);
	void addBeltEnchEffects(Equipment* e);
	void addBootsEnchEffects(Equipment* e);
	void addRingEnchEffects(Equipment* e);

	void removeWeaponEnchEffects(Weapon* w);
	void removeShieldEnchEffects(Equipment* e);
	void removeHelmetEnchEffects(Equipment* e);
	void removeArmorEnchEffects(Equipment* e);
	void removeBeltEnchEffects(Equipment* e);
	void removeBootsEnchEffects(Equipment* e);
	void removeRingEnchEffects(Equipment* e);

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & characterName;
		ar & characterClass;
		ar & level;
		ar & expPoints;
		ar & abilityScores;
		ar & currentHitPoints;
		ar & maxHitPoints;
		ar & equippedWeapon;
		ar & equipped;
		ar & backpack;
		ar & armorClass;
		ar & damageBonus;
		ar & isAlive;
		ar & baseAttackBonus;
		ar & attackBonus;
		ar & strengthModifier;
		ar & dexterityModifier;
		ar & intelligenceModifier;
		ar & wisdomModifier;
		ar & charismaModifier;
		ar & constitutionModifier;
	}

};