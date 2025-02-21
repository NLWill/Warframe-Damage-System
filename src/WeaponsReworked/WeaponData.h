#pragma once
#include <string>
#include <vector>
#include "src/WeaponsReworked/FiringMode.h"
#include "src/Weapons/Incarnon/Incarnon.h"
#include "src/Mods/ModPolarity.h"
#include "src/Mods/ModBase.h"

class WeaponDataReworked
{
public:
	int id;
	std::string name;
	std::string parent;
	std::vector<std::string> parents;
	std::string path;

	std::vector<FiringMode> behaviours;
	int ammoCapacity;
	int ammoClipSize;

	int normalModSlotCount, auraSlotCount, exilusSlotCount, arcaneSlotCount;
	std::vector<ModPolarity> artifactSlots;
	std::vector<std::string> compatibilityTags;
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