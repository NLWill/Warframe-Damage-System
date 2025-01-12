#pragma once
#include <vector>
#include <string>
#include "src/DamagePipeline/DamageInstance.h"
#include "src/Weapons/Weapon.h"
#include "src/Target/Target.h"

class FireInstance
{
public:
	FireInstance(Weapon &_weapon, std::string _attackName, Target &target, std::string targetBodyPart);
	std::vector<DamageInstance *> damageInstances;
	Weapon *weapon;
	std::string attackName;

	float moddedCriticalChance;
	float moddedCriticalDamage;
	float moddedStatusChance;
	float moddedStatusDamageMultiplier;
	float moddedMultishot;

	// Target Information
	Target *target; // Target class contains all data relevant to faction, hitzones etc.
	std::string targetBodyPart;

	std::vector<ModEffectBase *> GetAllModEffects(ModUpgradeType upgradeType);
	float GetTotalDamage();

private:
};