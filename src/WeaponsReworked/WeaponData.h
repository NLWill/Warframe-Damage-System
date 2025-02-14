#pragma once
#include <string>
#include <vector>
#include "src/WeaponsReworked/FiringMode.h"

class WeaponData
{
public:
	int ammoCapacity;
	int ammoClipSize;
	std::vector<std::string> artifactSlots;
	std::vector<FiringMode> behaviours;
	std::vector<std::string> compatibilityTags;
	std::vector<std::pair<std::string, int>> defaultSlottedUpgrades;
	float equipTime;
	std::vector<std::pair<int, std::string>> fireModes;
	std::string inventorySlot;
	bool isKuva;
	int levelCap;
	float omegaAttenuation;
	std::string productCategory;

private:
};