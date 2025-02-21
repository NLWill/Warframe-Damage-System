#pragma once
#include "src/Weapons/WeaponData.h"
#include <string>
#include <vector>
#include "src/Mods/ModManagerInterface.h"

class Weapon
{
public:
	Weapon(WeaponData &weaponData);
	~Weapon();
	WeaponData weaponData;

	ModManagerInterface *modManager;

	std::vector<ModEffectBase *> GetAllWeaponModEffects(ModUpgradeType upgradeType);
};