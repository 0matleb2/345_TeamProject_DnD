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

#include "boost/serialization/access.hpp"

class Character {

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


	std::string toString();


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



	int abilityScoreToModifier(int score);
	void levelUp();

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & _name;
		ar & _lvl;
		ar & _maxHp;
		ar & _strength;
		ar & _dexterity;
		ar & _constitution;
		ar & _intelligence;
		ar & _wisdom;
		ar & _charisma;
	}

};

