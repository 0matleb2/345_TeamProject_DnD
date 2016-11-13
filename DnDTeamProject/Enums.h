//! @file
//! @brief Header file for enumerated types used for Items and Enchantments
//!
//!I decided to use enumerated types to represent Stats and types of items as they are both finite sets.
#pragma once
#include <iostream>
#include <string>



//!enum for Statistics used in Enchantments
enum Stats { STR, DEX, CON, INT, WIS, CHA, AC, ATK, DMG };

//!enum for the different types of items
enum ItemType { HELMET, ARMOR, SHIELD, RING, BELT, BOOTS, WEAPON, OTHER };

enum WeaponType { MELEE, RANGED };

//!overload output operator to print enum names.
std::ostream& operator<<(std::ostream& op, Stats st);

std::ostream& operator<<(std::ostream& op, ItemType ty);

std::ostream& operator<<(std::ostream& op, WeaponType wt);

