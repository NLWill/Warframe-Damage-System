#pragma once
#include <string>
#include <vector>
#include <map>
#include "src/Weapons/FiringMode.h"
#include "src/Weapons/Incarnon/Incarnon.h"
#include "src/Mods/ModPolarity.h"
#include "src/Mods/ModBase.h"

class WeaponData
{
public:
	WeaponData();
	WeaponData(std::string name, std::map<std::string, FiringMode> firingModes);
	// The unique id number of the weapon
	int id;
	// The name of the weapon
	std::string name;
	// The weapon family that this weapon belongs to
	std::string parent;
	// A collection of other weapon families that the weapon inherits from
	std::vector<std::string> parents;
	// The file path leading to this weapon's data
	std::string path;

	// The collection of firing modes that the weapon is capable of firing
	std::map<std::string, FiringMode> firingModes;
	/// @brief Check whether the weapon contains a firing mode with the given attack name
	/// @param name 
	/// @return 
	bool IsValidFiringMode(std::string attackName);
	// The total ammunition that the weapon can carry
	int ammoCapacity;
	// The total ammunition within a single magazine
	int ammoClipSize;

	// A collection of compatability tags that can restrict or enable the equipping of certain mods
	std::vector<std::string> compatabilityTags;
	// The innate upgrades that the weapon includes, such as bonus headshot damage
	std::vector<shared_ptr<Mod>> defaultSlottedUpgrades;
	// A struct containing all the incarnon evolutions and enabling the selection of active upgrades
	Incarnon incarnonUpgrades;

	// The time until the weapon may be used when equipping it
	float equipTime;
	// Which inventory slot the weapon occupies
	std::string inventorySlot;
	// Boolean whether the weapon utilises the progenitor lich system
	bool isKuva;
	// The maximum level of the weapon, defining the mod capacity
	int levelCap;
	// The unique Riven disposition, scaling riven power for each weapon
	float omegaAttenuation;
	std::string productCategory;

private:
};