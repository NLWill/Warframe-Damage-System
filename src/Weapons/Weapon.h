#pragma once
#include "src/Weapons/WeaponData.h"
#include "src/Mods/ModManagerInterface.h"
#include<string>

class Weapon{
	public:
	Weapon(WeaponData &_data);

	WeaponData weaponData;
	ModManagerInterface *modManager;

	std::vector<ModEffectBase *> GetAllWeaponModEffects(ModUpgradeType upgradeType);

	//float Fire(Target target);
};