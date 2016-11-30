#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Types.h"
#include "Armor.h"
#include "Belt.h"
#include "Boots.h"
#include "Bracers.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
#include "ItemContainer.h"
#include "Chest.h"
#include "Observable.h"
#include "boost/serialization/access.hpp"

#include "Strategy.h"

class Map;

class Character : public Observable {

public:

	Character();
	
	~Character();


	int getX();
	int getY();
	std::string getName();
	int getLvl();
	int getHp();
	int getMaxHp();
	int getStrength();
	int getDexterity();
	int getConsitiution();
	int getIntelligence();
	int getWisdom();
	int getCharisma();
	Armor* getArmor();
	Belt* getBelt();
	Boots* getBoots();
	Bracers* getBracers();
	Helmet* getHelmet();
	Ring* getRing();
	Shield* getShield();
	Weapon* getWeapon();
	ItemContainer* getInventory();


	void setX(int x);
	void setY(int y);
	void setName(std::string name);
	void setLvl(int lvl);
	void setHp(int hp);
	void setMaxHp(int maxHp);
	void setStrength(int strength);
	void setDexterity(int dexterity);
	void setConsitiution(int constitution);
	void setIntelligence(int intelligence);
	void setWisdom(int wisdom);
	void setCharisma(int charisma);
	void setArmor(Armor* armor);
	void setBelt(Belt* belt);
	void setBoots(Boots* boots);
	void setBracers(Bracers* bracers);
	void setHelmet(Helmet* helmet);
	void setRing(Ring* ring);
	void setShield(Shield* shield);
	void setWeapon(Weapon* weapon);
	void setInventory(ItemContainer* inventory);

	int getTotalArmorClass();


	std::string toString();
	void scale(int targetLevel);
	void levelUp();
	static int abilityScoreToModifier(int score);

	void move(Map * context);
	void characterMenu();
	void equipItemMenu();
	void unequipItemMenu();
	void unequipItemMenu(Item * item);
	void discardItemMenu();
	void equip(Item * item);
	Character* selectAttackTarget(Map * context);
	bool npcInRange(Map * context);
	bool chestInRange(Map * context);
	Chest* selectLootTarget(Map* context);
	void loot(Chest * target, Map * context);
	void attack(Character* target, Map* context);

	bool operator==(const Character& character) const; //Needed for std::find()

	//strategy-related

	void setStrategy(int choice);
	void executeStrat(Map* context);

private:
	
	int _x;
	int _y;
	std::string _name;
	int _lvl;
	int _hp;
	int _maxHp;
	int _strength;
	int _dexterity;
	int _constitution;
	int _intelligence;
	int _wisdom;
	int _charisma;

	Armor* _armor;
	Belt* _belt;
	Boots* _boots;
	Bracers* _bracers;
	Helmet* _helmet;
	Ring* _ring;
	Shield* _shield;
	Weapon* _weapon;

	ItemContainer* _inventory;

	//strategy-related

	Strategy* _strategy;


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & _x;
		ar & _y;
		ar & _name;
		ar & _lvl;
		ar & _hp;
		ar & _maxHp;
		ar & _strength;
		ar & _dexterity;
		ar & _constitution;
		ar & _intelligence;
		ar & _wisdom;
		ar & _charisma;
		ar & _armor;
		ar & _belt;
		ar & _boots;
		ar & _bracers;
		ar & _helmet;
		ar & _ring;
		ar & _shield;
		ar & _weapon;
		ar & _inventory;
	}
};

