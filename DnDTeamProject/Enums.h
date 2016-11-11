//! @file
//! @brief Header file for enumerated types used for Items and Enchantments
//!
//!I decided to use enumerated types to represent stats and types of items as they are both finite sets.
#ifndef Enums_h
#define Enums_h

#include <iostream>
#include <string>

using namespace std;

//!enum for Statistics used in Enchantments
enum stats { STR, DEX, CON, INT, WIS, CHA, AC, ATK, DMG };

//!enum for the different types of items
enum itemType { HELMET, ARMOR, SHIELD, RING, BELT, BOOTS, WEAPON, OTHER };

enum weaponType { MELEE, RANGED };

//!overload output operator to print enum names.
ostream& operator<<(ostream& op, stats st);

ostream& operator<<(ostream& op, itemType ty);

ostream& operator<<(ostream& op, weaponType wt);

#endif