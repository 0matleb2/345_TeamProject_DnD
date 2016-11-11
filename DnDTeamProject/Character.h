#pragma once

#include <string>
#include "Item.h"
#include "Equipment.h"
#include "Weapon.h"
#include "Dice.h"
#include "ItemContainer.h"
#include "Observable.h"
using namespace std;

class Character: public Observable {
public:
	//constructors & destructor
	Character();								//default constructor
	Character(string, string, int);				//argument constructor 1
	Character(int, int, int, int, int, int);	//argument constructor 2
	Character(std::string name, std::string charaClass, int lvl, int str, int dex, int con, int intel, int wis, int cha); //argument constructor for CharacterMaker-generated character, meant for NPCs
	Character(const Character& orig);			//copy constructor
	~Character();								//destructor
	//getter methods for level & attributes
	string getCharacterName();
	string getCharacterClass();
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
	//getter methods for modifiers & bonuses
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
	//getter methods for equipment
	ItemContainer* getBackpack();
	Weapon* getEquippedWeapon();
	Equipment* getEquippedShield();
	Equipment* getEquippedHelmet();
	Equipment* getEquippedArmor();
	Equipment* getEquippedBelt();
	Equipment* getEquippedBoots();
	Equipment* getEquippedRing();
	//mutators for name, class, level, exp, and current HP
	void setName(string s);
	void setClass(string s);
	void setLevel(int i);
	void setExpPoints(int i);
	void setCurrentHitPoints(int i);
	//mutators for attributes
	void setStrength(int i);
	void setDexterity(int i);
	void setConstitution(int i);
	void setIntelligence(int i);
	void setWisdom(int i);
	void setCharisma(int i);
	//setter methods for equipment
	void setEquippedWeapon(Weapon*);
	void setEquippedShield(Equipment*);
	void setEquippedHelmet(Equipment*);
	void setEquippedArmor(Equipment*);
	void setEquippedBelt(Equipment*);
	void setEquippedBoots(Equipment*);
	void setEquippedRing(Equipment*);
	//testing methods
	bool validateNewCharacter();
	bool validateNewNPC();
	void printStats();
	void levelUpHitPointGain();
	void setInitialMaxHP(int lvl, int modifier);
	//in-game status changes
	//void attack(int x, int y);		//to be implemented
	void hit(int);
	void gainExp(int i);
	void printEquippedItems();
	//item-related actions
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

	//rescale level
	void rescale(int tgt_lvl);

	//serialization
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Observable>(*this);
		
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

private:
	string characterName;
	string characterClass;
	int level;
	int expPoints;
	//attributes
	//	index 0: strength
	//	index 1: dexterity
	//	index 2: constitution
	//	index 3: intelligence
	//	index 4: wisdom
	//	index 5: charisma
	int abilityScores[6];
	//ability modifiers
	int strengthModifier;
	int dexterityModifier;
	int intelligenceModifier;
	int wisdomModifier;
	int charismaModifier;
	int constitutionModifier;
	//status-related
	int maxHitPoints;
	int currentHitPoints;
	bool isAlive;
	//attack & damage bonus
	int armorClass;
	int damageBonus;
	//character-equipped items
	Weapon* equippedWeapon;
	//other equipped items:
	// index 0: Shield
	// index 1: Helmet
	// index 2: Armor
	// index 3: Belt
	// index 4: Boots
	// index 5: Ring
	Equipment* equipped[6];
	ItemContainer* backpack;
	int baseAttackBonus[4];
	int attackBonus[4];
	void updateBaseAttackBonus();
	void updateAttackBonus();
	//stats-setting & modifier updates (upon level-up or equipment change)
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

	//removing enchantment effects from unequipping items
	void removeWeaponEnchEffects(Weapon* w);
	void removeShieldEnchEffects(Equipment* e);
	void removeHelmetEnchEffects(Equipment* e);
	void removeArmorEnchEffects(Equipment* e);
	void removeBeltEnchEffects(Equipment* e);
	void removeBootsEnchEffects(Equipment* e);
	void removeRingEnchEffects(Equipment* e);
};