#pragma once
#include "src/WeaponsReworked/WeaponData.h"
#include <string>
#include <vector>
#include "src/Mods/ModManagerInterface.h"

class WeaponReworked
{
public:
	WeaponReworked(WeaponDataReworked &weaponData);
	WeaponDataReworked weaponData;

	//ModManagerInterface *modManager;

	std::vector<ModEffectBase *> GetAllWeaponModEffects(ModUpgradeType upgradeType);
};