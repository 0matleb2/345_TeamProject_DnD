//! @file
//! @brief Implementation of << operator overloads for enums.
//!

//#include "stdafx.h"
#include <iostream>
#include <string>

#include "Enums.h"

using namespace std;

//! overload for stats
ostream& operator<<(ostream& op, stats st)
{
	switch (st)
	{
	case STR: op << "Strength"; break;
	case DEX: op << "Dexterity"; break;
	case CON: op << "Constitution"; break;
	case INT: op << "Intelligence"; break;
	case WIS: op << "Wisdom"; break;
	case CHA: op << "Charisma"; break;
	case AC: op << "Armor Class"; break;
	case ATK: op << "Attack Bonus"; break;
	case DMG: op << "Damage Bonus"; break;
	default: op << "None";
	}

	return op;
}

//! overload for item categories
ostream& operator <<(ostream& op, itemType ty)
{
	switch (ty)
	{
	case HELMET: op << "Helmet"; break;
	case ARMOR: op << "Armor"; break;
	case SHIELD: op << "Shield"; break;
	case RING: op << "Ring"; break;
	case BELT: op << "Belt"; break;
	case BOOTS: op << "Boots"; break;
	case WEAPON: op << "Weapon"; break;
	default: op << "Other";
	}

	return op;
}

ostream& operator <<(ostream& op, weaponType wt)
{
	switch (wt)
	{
	case MELEE: op << "Melee"; break;
	case RANGED: op << "Ranged"; break;
	default: op << "Other"; break;
	}

	return op;
}