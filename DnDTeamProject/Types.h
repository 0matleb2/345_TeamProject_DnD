#pragma once
#include <map>
#include "boost\serialization\access.hpp"



enum class ArmorType {
	DEFAULT = 0,
	PADDED,
	LEATHER,
	STUDDED_LEATHER,
	CHAIN_SHIRT,
	BREASTPLATE,
	BANDED_MAIL,
	HALF_PLATE,
	PLATE


};
static std::map<ArmorType, std::string> armorTypeInfo = {
	{ ArmorType::PADDED, "Padded armor" },
	{ ArmorType::LEATHER, "Leather armor" },
	{ ArmorType::STUDDED_LEATHER, "Studded leather armor" },
	{ ArmorType::CHAIN_SHIRT, "Chain shirt" },
	{ ArmorType::BREASTPLATE, "Breastplate" },
	{ ArmorType::BANDED_MAIL, "Banded mail armor" },
	{ ArmorType::HALF_PLATE, "Half plate armor" },
	{ ArmorType::PLATE, "Plate armor" }
};
template<class Archive> void serialize(Archive & ar, ArmorType armorType, const unsigned int version) {
	ar & armorType;
}



enum class ShieldType {
	DEFAULT = 0,
	BUCKLER,
	HEAVY_SHIELD,
	TOWER_SHIELD
};
static std::map<ShieldType, std::string> shieldTypeInfo = {
	{ ShieldType::BUCKLER, "Buckler" },
	{ ShieldType::HEAVY_SHIELD, "Heavy shield" },
	{ ShieldType::TOWER_SHIELD, "Tower shield" }
};
template<class Archive> void serialize(Archive & ar, ShieldType shieldType, const unsigned int version) {
	ar & shieldType;
}



enum class WeaponType {
	DEFAULT = 0,
	LONGSWORD,
	LONGBOW
};
static std::map<WeaponType, std::string> weaponTypeInfo = {
	{ WeaponType::LONGSWORD, "Longsword" },
	{ WeaponType::LONGBOW, "Longbow" }
};
template<class Archive> void serialize(Archive & ar, WeaponType weaponType, const unsigned int version) {
	ar & weaponType;
}
