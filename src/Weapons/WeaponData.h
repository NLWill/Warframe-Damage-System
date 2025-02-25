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
	int id;
	std::string name;
	std::string parent;
	std::vector<std::string> parents;
	std::string path;

	std::map<std::string, FiringMode> firingModes;
	bool IsValidFiringMode(std::string name);
	int ammoCapacity;
	int ammoClipSize;

	int normalModSlotCount, auraSlotCount, exilusSlotCount, arcaneSlotCount;
	std::vector<ModPolarity> modPolarities;
	std::vector<std::string> compatabilityTags;
	std::vector<Mod *> defaultSlottedUpgrades;
	Incarnon incarnonUpgrades;

	float equipTime;
	std::string inventorySlot;
	bool isKuva;
	int levelCap;
	float omegaAttenuation;
	std::string productCategory;

private:
};