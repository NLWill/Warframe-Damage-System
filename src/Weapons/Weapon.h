#pragma once
#include "src/Weapons/WeaponData.h"
#include <string>
#include <vector>
#include "src/Mods/ModManagerInterface.h"
#include "src/Target/Target.h"

class Weapon
{
public:
	Weapon(WeaponData &weaponData);
	~Weapon();
	WeaponData weaponData;

	ModManagerInterface *modManager;

	std::vector<ModEffectBase *> GetAllWeaponModEffects(ModUpgradeType upgradeType);

	float Fire(std::string attackName, Target &target, std::string targetBodyPart);
	float GetAverageDamagePerShot(std::string attackName, Target &target, std::string targetBodyPart);
	float GetAverageBurstDPS(std::string attackName, Target &target, std::string targetBodyPart);
	float GetAverageSustainedDPS(std::string attackName, Target &target, std::string targetBodyPart);

	float GetFireRate(std::string attackName);
	float GetChargeTime(std::string attackName);
	int GetMagazineCapacity();
	float GetReloadTime(std::string attackName);
};