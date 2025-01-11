#pragma once
#include <vector>
#include <string>
#include "src/DamagePipeline/DamageInstance.h"
#include "include/Weapons/Weapon.h"

class FireInstance
{
public:
	FireInstance(Weapon &_weapon, std::string _attackName);
	std::vector<DamageInstance *> damageInstances;
	Weapon *weapon;
	std::string attackName;

	float moddedCriticalChance;
	float moddedCriticalDamage;
	float moddedStatusChance;
	float moddedStatusDamageMultiplier;
	float moddedMultishot;

	// Target Information
	// Target* target;	Target class contains all data relevant to faction, hitzones etc.

	std::vector<ModEffectBase *> GetAllModEffects(ModUpgradeType upgradeType);

private:
};